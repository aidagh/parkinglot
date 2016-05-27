//File:         JobModel.cpp
//Description:

#include "JobModel.hpp"

std::map<int, Job*> JobModel::jobMap;
std::queue<Job*> JobModel::jobQueue;
int JobModel::numJobs = 1;

void JobModel::Initialize()
{

}

void JobModel::HandleJobs()
{
  HandleJobProcessing();

  HandleJobDataMigration_ReserveTransaction();
  HandleJobVMMigration_ReserveTransaction();

  HandleJobDataMigration_CompleteTransaction();
  HandleJobVMMigration_CompleteTransaction();

  HandleCompletedJobs();
  HandleIncomingJobs();
}


Job * JobModel::GenerateJob()
{
  Job * job = new Job();
  job->job_number = numJobs;
  job->jobSize = _jobDistributionModel.getNextJobLength();
  job->jobSizeLeftToProcess = job->jobSize;
  job->VMsize = _jobDistributionModel.getNextVMSize();
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
		std::list<MigrationJob*>::iterator itMJ;
        for(itMJ = job->DataMigrationJobs.begin(); itMJ != job->DataMigrationJobs.end(); itMJ++)
        {
            if ((*itMJ)->type == Data)
            {
                _networkModel.ReserveBandwidth(*itMJ);
            }
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

	//If there are data migration jobs, but the job is not "DataMigrating" then the job is not active.
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
				itMJ--;
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


void JobModel::HandleJobVMMigration_ReserveTransaction()
{
  NetworkModel _networkModel;
  std::map<int, Job*>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++)
  {
    Job* job = it->second;

	//If the job is not yet fully complete, but the processing is complete, then the vehicle is backing up data
	if (job->jobStatus == VMMigrating)
	{
        _networkModel.ReserveBandwidth(job->VMMigrationJob);
	}
  }
}

void JobModel::HandleJobVMMigration_CompleteTransaction()
{
    std::list<int> jobEraseList;
    std::map<int, Job*>::iterator it;
    for(it = jobMap.begin(); it != jobMap.end(); it++)
    {
        Job* job = it->second;

        if (job->jobStatus == VMMigrating)
        {
            job->VMMigrationJob->dataLeftToMigrate = job->VMMigrationJob->dataLeftToMigrate - job->VMMigrationJob->currentBandwidthSize;
            if (job->VMMigrationJob->dataLeftToMigrate <=0)
            {
                //**Some statistics should be kept up here.



                job->car->job = NULL;
                job->car = job->VMMigrationJob->carTo;

                //Add the record to the jobMap for the TO car
                jobMap[job->car->car_spot_number] = job;

                delete job->VMMigrationJob;
                job->VMMigrationJob = NULL;

                *_log.info << "Space:" << it->first << " -- VM Complete!" << std::endl;

                //Erase the record from the jobMap for the FROM car
                it = jobMap.erase(it);
                it--;

                //Is it always appropriate to set this to Processing?
                job->jobStatus = Processing;
            }
        }
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
  //1. Get the job from the jobMap using the space
  //2. Check the job status and handle appropriately.
  //   a. If processing  [Can this happen?]
  //   b. If data Migration [Can this happen?]
  //   c. If vm Migrating [Cancel Migration and log VM Migration Failure]
  //3. Delete the job
  //4. clear the spaceId from the JobMap

  if (jobMap.find(spaceId) != jobMap.end())
  {
      Job * job = jobMap[spaceId];

      if (job->jobStatus == Processing)
      {
        *_log.debug << "Possible Issue - Job failed while Processing " << spaceId << std::endl;
      }
      else if (job->jobStatus == DataMigrating)
      {
        *_log.debug << "Possible Issue - Job failed while DataMigrating " << spaceId << std::endl;
      }
      else if (job->jobStatus == VMMigrating)
      {

        job->VMMigrationJob->carTo->job = NULL;
        *_log.debug << "Migration Failure - Job failed while VM Migration From " << spaceId << " to " << job->VMMigrationJob->carTo->car_spot_number << std::endl;

        delete job->VMMigrationJob;
      }


      delete job;
      //Handle Statistics!
      jobMap.erase(spaceId);



      *_log.debug << "Erased job in space" << spaceId << std::endl;
  }
  else
  {
        *_log.debug << "No job to erase in space" << spaceId << std::endl;

  }
}

void JobModel::SetupVMMigration(Car* leavingCar, Car* carToMigrateTo)
{
    //1. leavingCar->job should already equal the job.
    //2. set carToMigrateTo->job to the job.
    //3. Create a new VMMigrationJob vmMigrationJob
    //   a. set vmMigrationJob->jobFrom to the Job
    //   b. set vmMigrationJob->carFrom to leavingCar
    //   c. set vmMigrationJob->carTo to carToMigrateTo
    //   d. set vmMigrationJob->type to VM
    //   e. set vmMigrationJob->totalDataSize to job->VMSize
    //   f. set vmMigrationJob->dataLeftToMigrate to job->VMSize
    //   g. set vmMigrationJob->currentBandwidthSize to 1  ****Reset this when the congestion model is complete.
    //4. set job->VMMigrationJob = vmMigrationJob;

    Job * job = leavingCar->job;
	carToMigrateTo->job = job;
    MigrationJob * vmMigrationJob = new MigrationJob;
    vmMigrationJob->jobFrom = job;
    vmMigrationJob->carFrom = leavingCar;
    vmMigrationJob->carTo = carToMigrateTo;
    vmMigrationJob->type = VM;
    vmMigrationJob->totalDataSize = job->VMsize;
    vmMigrationJob->dataLeftToMigrate = job->VMsize;
    //  ****Reset this when the congestion model is complete.
    vmMigrationJob->currentBandwidthSize = 1;
    job->VMMigrationJob = vmMigrationJob;


	*_log.info << "Job " << job->job_number << " from Car " << leavingCar->car_spot_number << "to Car " << carToMigrateTo->car_spot_number << std::endl;
}
