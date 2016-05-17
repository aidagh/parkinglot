//File:         JobModel.cpp
//Description:

#include "JobModel.hpp"

std::map<int, Job*> JobModel::jobMap;
std::queue<Job*> JobModel::jobQueue;
int JobModel::numJobs = 0;

void JobModel::Initialize()
{

}

void JobModel::HandleJobs()
{
  HandleJobProcessing();

  HandleJobDataMigration_ReserveTransaction();
  //HandleJobVMMigration_ReserveTransaction();

  HandleJobDataMigration_CompleteTransaction();
  //HandleJobVMMigration_CompleteTransaction();
  HandleJobVMMigration();

  HandleCompletedJobs();
  HandleIncomingJobs();
}


Job * JobModel::GenerateJob()
{
  Job * job = new Job();
  job->job_number = numJobs;
  job->jobSize = _jobDistributionModel.getNextJobLength();  //Get this from distribution class
  job->jobSizeLeftToProcess = job->jobSize;
  job->VM_size = _jobDistributionModel.getNextVMSize();
  job->jobStatus = Processing;

  job->dataToMigrate = _jobDistributionModel.getNextDataSize();

  _jobDistributionModel.generateNext();
  numJobs++;
  return job;
}

void JobModel::createNewJob()
{
	CarModel _carModel;
	Job* job = GenerateJob();
	Car* car = _carModel.AssignJob(job);

	if (car != NULL)
	{
      *_log.info << "New Job assigned to car:" << car->car_spot_number << std::endl;
//	  job->car_number = car->car_number;
	  job->car = car;
	  jobMap[car->car_spot_number] = job;
	}
	else
	{
      *_log.info << "New Job assigned to JobQueue:" << std::endl;

      jobQueue.push(job);
	}


}

void JobModel::SetJobToDataMigrating(Job * job)
{
    *_log.trace << "Entering SetJobToDataMigrating()" << std::endl;
    CarModel carModel;

    *_log.info << "Data Migration Setup" << std::endl;
    *_log.info << "   From Car: " << job->car->car_spot_number << std::endl;

	//1. Set job to DataMigrating
	//2. Populate DataMigrationJobs
    //3. Update Car in MigrationSet with a MigrationJob * of the job it is holding data for.
	job->jobStatus = DataMigrating;

	std::list<Car*> migrationSet = carModel.AssignDataMigrationCars(job);

	//Loop through migration cars
	std::list<Car*>::iterator it;
	for(it=migrationSet.begin(); it != migrationSet.end(); it++)
    {
        //  Create the MigrationJob
        MigrationJob * migrationJob = new MigrationJob();
        migrationJob->jobFrom = job;
        migrationJob->carFrom = job->car;
        migrationJob->carTo = *it;
        migrationJob->type = Data;
        migrationJob->totalDataSize = job->dataToMigrate;
        migrationJob->dataLeftToMigrate = job->dataToMigrate;
        //  Set the MigrationJob on the car
        job->DataMigrationJobs.push_back(migrationJob);
        //  Add the Migration Job to the job->DataMigrationJobs
        (*it)->DataMigrationTasks.push_back(migrationJob);

        *_log.info << "   To Car: " << (*it)->car_spot_number << std::endl;

    }

    *_log.trace << "Exiting SetJObToDataMigrating()" << std::endl;

}

void JobModel::HandleJobProcessing()
{
  std::map<int, Job*>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++)
  {
    Job* job = it->second;

//	*_log.debug << "Space:" << it->first << ", leftToProcess:" << job->jobSizeLeftToProcess << ", leftToMigrate:" << job->dataLeftToMigrate << ", Status:" << job->jobStatus << std::endl;


    //If the job is still processing, then
	if (job->jobStatus == Processing)
	{
      //subtract time from the time left to process
      job->jobSizeLeftToProcess-=_configuration.TimeStep;

      //If the job is no longer processing
      if (job->jobSizeLeftToProcess <= 0)
	  {
		//Set the job to ProcessingComplete
        SetJobToDataMigrating(job);
	  }

	}
  }


}

void JobModel::HandleJobDataMigration_ReserveTransaction()
{
  NetworkModel _networkModel;
  std::map<int, Job*>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++)
  {
    Job* job = it->second;

	//If the job is not yet fully complete, but the processing is complete, then the vehicle is backing up data
	if (job->jobStatus == DataMigrating)
	{
        //Since a job cannot be DataMigrating AND VMMigrating at the same time, the ActiveMigrationJobs will only have Data Migrations
		std::list<MigrationJob*>::iterator itMJ;
        for(itMJ = job->DataMigrationJobs.begin(); itMJ != job->DataMigrationJobs.end(); itMJ++)
        {
			_networkModel.ReserveBandwidth(*itMJ);
		}
	}
  }
}

void JobModel::HandleJobDataMigration_CompleteTransaction()
{
  std::list<int> jobEraseList;

  std::map<int, Job*>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++)
  {
    Job* job = it->second;

	//If the job is not yet fully complete, but the processing is complete, then the vehicle is backing up data
	if (job->jobStatus == DataMigrating)
	{
		std::list<MigrationJob*>::iterator itMJ;
        for(itMJ = job->DataMigrationJobs.begin(); itMJ != job->DataMigrationJobs.end(); ++itMJ)
        {
			(*itMJ)->dataLeftToMigrate = (*itMJ)->dataLeftToMigrate - (*itMJ)->currentBandwidthSize;
			if ((*itMJ)->dataLeftToMigrate <=0)
			{
				//**Some statistics should be kept up here.
				//**Update the list of DataMigrationSet vehicles.
				(*itMJ)->carTo->DataMigrationTasks.remove(*itMJ);
				itMJ = job->DataMigrationJobs.erase(itMJ);
			}
		}

		if (job->DataMigrationJobs.empty())
		{
			*_log.info << "Space:" << it->first << " -- Job Complete!" << std::endl;

			job->jobStatus = Complete;
		    //TODO: update statistics
			jobEraseList.push_back(it->first);
            job->car->job = NULL;
		}
	}
  }

  std::list<int>::iterator itList;
  for(itList = jobEraseList.begin(); itList != jobEraseList.end(); itList++)
  {
    jobMap.erase(*itList);
  }
}

void JobModel::HandleJobVMMigration()
{
  std::list<int> jobEraseList;
  std::map<int, Job*>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++)
  {
    Job* job = it->second;
  //Determine Congestion and Available Bandwidth Here
  //TODO:

	if (job->jobStatus == VMMigrating)
	{
		//Migrate VM here
		//TODO: incorporate congestion
		//job->VM_migration_remained-=1;

		if (false/*job->VM_migration_remained <= 0*/)
		{
			*_log.info << "Space:" << it->first << " -- VM Complete!" << std::endl;

			//VM Completion
			//1. job is the job being migrated
			//2. Set job->MigrateFromCar->job to NULL
			//3. Set job->car to job->MigrateToCar
			//4. Set job->MigrateFromCar to NULL
			//5. Set job->MigrateToCar to NULL
			//6. Set Status to either Processing or Data Migration.
            //7. Update Statistics

            job->MigrateFromCar->job = NULL;
			job->car = job->MigrateToCar;
			job->MigrateFromCar = NULL;
			job->MigrateToCar = NULL;

			//Do we restart the job processing, or data migration?
			job->jobStatus = Processing;

		    //TODO: update statistics


		}
	}
  }

  std::list<int>::iterator itList;
  for(itList = jobEraseList.begin(); itList != jobEraseList.end(); itList++)
  {
    jobMap.erase(*itList);
  }


}


void JobModel::HandleIncomingJobs()
{
    //TODO: Handle jobs in Queue First
	//      If the queue is populated, add any new jobs directly to the queue.

    while (_time.getTime() >= _jobDistributionModel.getNextArrival())
	{
		createNewJob();
	}
}


void JobModel::HandleCompletedJobs()
{
 /* std::map<int, Job>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++)
  {
    Job* job = &(it->second);


  }
	*/
}


void JobModel::CancelJob(int spaceId)
{
  Job * job = jobMap[spaceId];
  //Handle Statistics!
  jobMap.erase(spaceId);
  *_log.debug << "Erased job in space" << spaceId << std::endl;

}

void JobModel::SetupVMMigration(Car* leavingCar, Car* carToMigrateTo)
{
    //1. leavingCar->job should already equal the job.
	//2. set carToMigrateTo->job to the job.
	//3. Set job->MigrateToCar to carToMigrateTo
	//4. Set job->MigrateFromCar to leaving Car.

    Job * job = leavingCar->job;
	carToMigrateTo->job = job;
	job->MigrateToCar = carToMigrateTo;
	job->MigrateFromCar = leavingCar;

//	leavingCar->job->VM_migration_remained = leavingCar->job->VM_size;
//    leavingCar->job->MigrateToCar = carToMigrateTo;
//    leavingCar->job->jobStatus = VMMigratingAwayFrom;
//
//	Job * MigrateToJob = new Job();
//	leavingCar->job->MigrateToJob = MigrateToJob;
//	MigrateToJob->job_number = leavingCar->job->job_number;
//	MigrateToJob->VM_size = 0;
//    MigrateToJob->MigrateFromCar = leavingCar;
//    MigrateToJob->jobStatus = VMMigratingTo;
//	MigrateToJob->jobSize = leavingCar->job->jobSize;
//	MigrateToJob->jobSizeLeftToProcess = leavingCar->job->jobSizeLeftToProcess;
//	MigrateToJob->dataToMigrate = leavingCar->job->dataToMigrate;
//	MigrateToJob->dataLeftToMigrate = leavingCar->job->dataLeftToMigrate;
//
//    carToMigrateTo->job = MigrateToJob;

	*_log.info << "Job " << job->job_number << " from Car " << leavingCar->car_spot_number << "to Car " << carToMigrateTo->car_spot_number << std::endl;
}
