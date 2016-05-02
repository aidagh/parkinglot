#include "JobModel.hpp"

void JobModel::Initialize()
{	
	
}

Job * JobModel::GenerateJob()
{
  Job * job = new Job();
  job->job_number = numJobs;  
  job->jobSize = _jobDistributionModel.getNextJobLength();  //Get this from distribution class	
  job->jobSizeLeftToProcess = job->jobSize;
  job->VM_size = _jobDistributionModel.getNextVMSize();
  job->jobStatus = Processing;

  job->dataToMigrate = _jobDistributionModel.getNextJobDataToMigrate();		
  job->dataLeftToMigrate = 0;
  
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
	  job->car_number = car->car_number;
	  job->car = car;
	  jobMap[car->car_spot_number] = job;
	}
	else
	{
      *_log.info << "New Job assigned to JobQueue:" << std::endl;

      jobQueue.push(job);	
	}
	
	
}



void JobModel::HandleJobProcessing()
{
  std::map<int, Job*>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++) 
  {
    Job* job = it->second;

	*_log.debug << "Space:" << it->first << ", leftToProcess:" << job->jobSizeLeftToProcess << ", leftToMigrate:" << job->dataLeftToMigrate << ", Status:" << job->jobStatus << std::endl;
	
	
	//TODO: move away from bools as statuses and use a Status enum
    //If the job is still processing, then 
	if (job->jobStatus == Processing)
	{
      //subtract time from the time left to process
      job->jobSizeLeftToProcess-=_configuration.TimeStep;
  	
      //If the job is no longer processing
      if (job->jobSizeLeftToProcess <= 0)
	  {
		//Set the job to ProcessingComplete
		job->jobStatus = DataMigrating;
	  } 

	}
  }
  
			
}

void JobModel::HandleJobDataMigration()
{
  std::list<int> jobEraseList;

  std::map<int, Job*>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++) 
  {
    Job* job = it->second;
  //Determine Congestion and Available Bandwidth Here
  //TODO: 

	//If the job is not yet fully complete, but the processing is complete, then the vehicle is backing up data
	if (job->jobStatus == DataMigrating)
	{		
		//Migrate Data here
		
	
		
		if (job->dataLeftToMigrate <= 0)
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

	if (job->jobStatus == VMMigratingAwayFrom)
	{		
		//Migrate VM here
		//TODO: incorporate congestion
		job->VM_migration_remained-=1;
				
		if (job->VM_migration_remained <= 0)
		{
			*_log.info << "Space:" << it->first << " -- VM Complete!" << std::endl;

			//Do we restart the job processing, or data migration?
			job->jobStatus = VMMigrationComplete;
			
			
			Job* migratedJob = job->MigrateToJob;
			migratedJob->jobStatus = Processing;
			
		    //TODO: update statistics	

			
            //Remove the job that was being migrated.
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

void JobModel::Migrate(Car* leavingCar, Car* carToMigrateTo)
{

	leavingCar->job->VM_migration_remained = leavingCar->job->VM_size;
    leavingCar->job->MigrateToCar = carToMigrateTo;
    leavingCar->job->jobStatus = VMMigratingAwayFrom;

	Job * MigrateToJob = new Job();
	leavingCar->job->MigrateToJob = MigrateToJob;
	MigrateToJob->job_number = leavingCar->job->job_number;
	MigrateToJob->VM_size = 0;
    MigrateToJob->MigrateFromCar = leavingCar;
    MigrateToJob->jobStatus = VMMigratingTo;	
	MigrateToJob->jobSize = leavingCar->job->jobSize;
	MigrateToJob->jobSizeLeftToProcess = leavingCar->job->jobSizeLeftToProcess;
	MigrateToJob->dataToMigrate = leavingCar->job->dataToMigrate;
	MigrateToJob->dataLeftToMigrate = leavingCar->job->dataLeftToMigrate;
	
    carToMigrateTo->job = MigrateToJob;
	
	*_log.info << "Job " << leavingCar->job->job_number << " from Car " << leavingCar->car_spot_number << "to Car " << carToMigrateTo->car_spot_number << std::endl;
}
