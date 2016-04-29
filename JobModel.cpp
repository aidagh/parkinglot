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
  

  job->dataToMigrate = _jobDistributionModel.getNextJobDataToMigrate();		
  job->dataLeftToMigrate = 0;
  
  _jobDistributionModel.generateNext();
  numJobs++;
  return job;
}

void JobModel::createNewJob()
{
	Job* job = GenerateJob();
	Car* car = _carModel.AssignJob(job);
	
	if (car != NULL)
	{
	  job->car_number = car->car_number;
	  job->car = car;
	  jobMap[car->car_spot_number] = *job;
	}
	else
	{
	  jobQueue.push(*job);	
	}
	
	
}


void JobModel::HandleJobProcessing()
{
  std::map<int, Job>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++) 
  {
    Job* job = &(it->second);

	std::cout << "Space:" << it->first << ", leftToProcess:" << job->jobSizeLeftToProcess << ", leftToMigrate:" << job->dataLeftToMigrate << std::endl;
	
	
	//TODO: move away from bools as statuses and use a Status enum
    //If the job is still processing, then 
	if (!job->jobProcessingComplete)
	{
      //subtract time from the time left to process
      job->jobSizeLeftToProcess-=_configuration.TimeStep;
  	
      //If the job is no longer processing
      if (job->jobSizeLeftToProcess <= 0)
	  {
		//Set the job to ProcessingComplete
		job->jobProcessingComplete = true;
	  } 

	}
  }
  
  //Determine Congestion and Available Bandwidth Here
  //TODO: 

  std::list<int> jobEraseList;
  for(it = jobMap.begin(); it != jobMap.end() && !jobMap.empty() ; it++) 
  {
    Job* job = &(it->second);

	//If the job is not yet fully complete, but the processing is complete, then the vehicle is backing up data
	if (!job->jobComplete && job->jobProcessingComplete)
	{		
		//Migrate Data here
		
		
		
		
		
		if (job->dataLeftToMigrate <= 0)
		{
			std::cout << "Space:" << it->first << " -- Job Complete!" << std::endl;
			
			job->jobComplete = true;
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
  std::map<int, Job>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++) 
  {
    Job* job = &(it->second);
	
	  
  }
	
}