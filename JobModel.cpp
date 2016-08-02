//File:         JobModel.cpp
//Description:

#include "JobModel.hpp"

std::map<int, Job*> JobModel::jobMap;
jobPQ_type JobModel::jobQueue(comparison(true));
int JobModel::numJobs = 1;

void JobModel::Initialize()
{

}

void JobModel::HandleJobs()
{
  HandleIncomingJobs();
  HandleJobProcessing();

  handleMigrationJobsAtDataCenter_ReserveTransaction();
  HandleJobDataMigration_ReserveTransaction();
  HandleJobVMMigration_ReserveTransaction();

  NetworkModel _networkModel;
  _networkModel.Allocate();

  handleMigrationJobsAtDataCenter_CompleteTransaction();
  HandleJobDataMigration_CompleteTransaction();
  HandleJobVMMigration_CompleteTransaction();

  HandleCompletedJobs();
}


Job * JobModel::GenerateJob()
{
  int jobLength = _jobDistributionModel.getNextJobLength();
  int jobDataToMigrate = _jobDistributionModel.getNextDataSize();

  Job * job = new Job();
  job->job_number = numJobs;
  job->jobProcessingTime = jobLength;
  job->jobProcessingTimeLeft = jobLength;
  job->VMsize = _jobDistributionModel.getNextVMSize();
  job->dataToMigrate = jobDataToMigrate;

  job->JobArrivalTime = _time.getTime();

  if (_configuration.TaskScheme_AlternateProcessAndDataMigrate)
  {
      JobTaskType taskType = Task_Process;

      //Only half the tasks are Processing tasks, so divide by 2
      int jobLengthPerTask = jobLength / (_configuration.NumberTasksPerJob / 2);
      //Only half the tasks are Migration tasks, so divide by 2
      int DataToMigratePerTask = jobDataToMigrate / (_configuration.NumberTasksPerJob / 2);

      for(int i=0; i<_configuration.NumberTasksPerJob-1; i++)
      {
          JobTask* task = new JobTask;
          task->job = job;
          task->taskType = taskType;
          if (taskType == Task_Process)
          {
              task->taskProcessingTime = jobLengthPerTask;
              task->taskProcessingTimeLeft = jobLengthPerTask;
              taskType = Task_DataMigrate;
              if (i == 0)
              {
                  job->ActiveJobTask = task;
                  task->jobTaskStatus = Task_InProgress;
                  //job->jobStatus = Processing;
              }

          }
          else if (taskType == Task_DataMigrate)
          {
              task->taskDataToMigrate = DataToMigratePerTask;
              taskType = Task_Process;
              if (i == 0)
              {
                  job->ActiveJobTask = task;
                  //job->jobStatus = DataMigrating;
              }

          }
          job->JobTasks.push_back(task);
      }
  }
//  else if (_configuration.TaskScheme_AlternateProcessAndDataMigrateWithInitialAndFinalLoadtoDC)
//  {
//      JobTaskType taskType = Task_InitialVMMigrate;
//
//      //Add InitialVMMigration Job
//      JobTask* task = new JobTask;
//      task->job = job;
//      task->taskDataToMigrate = job->VMsize;
//      task->taskType = Task_InitialVMMigrate;
//      task->jobTaskStatus = Task_InProgress;
//      job->ActiveJobTask = task;
//      job->jobStatus = InitialSetup;
//      job->JobTasks.push_back(task);
//
//      //Add InitialDataMigration Job
//      task = new JobTask;
//      task->job = job;
//      task->taskDataToMigrate = jobDataToMigrate;
//      task->taskType = Task_InitialDataMigrate;
//      job->JobTasks.push_back(task);
//
//
//      //Only half the tasks are Processing tasks, so divide by 2
//      // -1 because the last data is transferred to the DC
//      int jobLengthPerTask = jobLength / (_configuration.NumberTasksPerJob / 2) - 1;
//
//      //Only half the tasks are Migration tasks, so divide by 2
//      int DataToMigratePerTask = jobDataToMigrate / (_configuration.NumberTasksPerJob / 2);
//
//      for(int i=0; i<_configuration.NumberTasksPerJob; i++)
//      {
//          JobTask* task = new JobTask;
//          task->job = job;
//          task->taskType = taskType;
//          if (taskType == Task_Process)
//          {
//              task->taskProcessingTime = jobLengthPerTask;
//              task->taskProcessingTimeLeft = jobLengthPerTask;
//              taskType = Task_DataMigrate;
//              if (i == 0)
//              {
//                  job->ActiveJobTask = task;
//                  task->jobTaskStatus = Task_InProgress;
//                  job->jobStatus = Processing;
//              }
//
//          }
//          else if (taskType == Task_DataMigrate)
//          {
//              task->taskDataToMigrate = DataToMigratePerTask;
//              taskType = Task_Process;
//              if (i == 0)
//              {
//                  job->ActiveJobTask = task;
//                  job->jobStatus = DataMigrating;
//              }
//
//          }
//          job->JobTasks.push_back(task);
//      }
//
//        //Add InitialDataMigration Job
//      task = new JobTask;
//      task->job = job;
//      task->taskDataToMigrate = jobDataToMigrate;
//      task->taskType = Task_FinalDataMigrate;
//      job->JobTasks.push_back(task);
//
//  }
   else
  {
    *_log.debug << "Error: No Job Task Scheme Defined" << std::endl;
  }

  _jobDistributionModel.generateNext();
  numJobs++;
  return job;
}

void JobModel::createNewJob()
{
	//CarModel _carModel;
	Job* job = GenerateJob();
	//Car* car = _carModel.AssignJob(job);
    *_log.info << "New Job assigned to JobQueue:" << std::endl;
    jobQueue.push(job);
    /*
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
	}*/


}
void JobModel::SetActiveTaskComplete(Job * job)
{
    job->ActiveJobTask->jobTaskStatus = Task_Complete;
}



void JobModel::StartNextJobTask(Job * job)
{

    std::list<int> jobEraseList;
    bool found = false;

    //I think this can be done with iterators in a better way.
    std::list<JobTask*>::iterator it;
	for(it=job->JobTasks.begin(); it != job->JobTasks.end(); it++)
    {
        if ((*it)->jobTaskStatus != Task_Complete)
        {
            job->ActiveJobTask = (*it);
            found = true;
            job->ActiveJobTask->jobTaskStatus = Task_InProgress;

            if (job->ActiveJobTask->taskType == Task_DataMigrate)
            {
                SetJobToDataMigrating(job);
            }
            if (job->ActiveJobTask->taskType == Task_Process)
            {
                SetJobToDataProcessing(job);
            }

            break;
        }
    }

    if (found == false)
    {
        job->jobStatus = FinalMigration;
        addMigrationJobToDataCenter(job, job->car);
    }


/*
    std::list<int>::iterator itList;
    for(itList = jobEraseList.begin(); itList != jobEraseList.end(); itList++)
    {
        jobMap.erase(*itList);
    }
*/
}




void JobModel::SetJobToDataMigrating(Job * job)
{
    *_log.trace << "Entering SetJobToDataMigrating()" << std::endl;
    CarModel carModel;

    *_log.info << "Data Migration Setup" << std::endl;
    *_log.info << "   From Car: " << job->car->car_spot_number << ", cluster number: "
                                  << job->car->car_cluster_number << ", group number: "
                                  << job->car->car_group_number << ", region number: "
                                  << job->car->car_region_number << std::endl;

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
        migrationJob->totalDataSize = job->ActiveJobTask->taskDataToMigrate;
        migrationJob->dataLeftToMigrate = job->ActiveJobTask->taskDataToMigrate;
        //  Set the MigrationJob on the car
        job->DataMigrationJobs.push_back(migrationJob);
        //  Add the Migration Job to the job->DataMigrationJobs
        (*it)->ActiveDataMigrationTasks.push_back(migrationJob);

        *_log.info << "   To Car: " << (*it)->car_spot_number << ", cluster number: "
                                  << (*it)->car_cluster_number << ", group number: "
                                  << (*it)->car_group_number << ", region number: "
                                  << (*it)->car_region_number << std::endl;

    }

    *_log.trace << "Exiting SetJObToDataMigrating()" << std::endl;

}

void JobModel::SetJobToDataProcessing(Job * job)
{
    *_log.trace << "Entering SetJobToDataProcessing()" << std::endl;

	job->jobStatus = Processing;


    *_log.trace << "Exiting SetJObToDataProcessing()" << std::endl;

}

void JobModel::SetJobComplete(Job *job)
{

        *_log.info << "Space:" << job->car->car_spot_number << " -- Job Complete!" << std::endl;


        job->jobStatus = Complete;
        //It seems silly to set this now, but we may want to print these out in the future.
        job->JobEndTime = _time.getTime();

        _statisticsModel.LogJobCompleted();

        _statisticsModel.LogJobCompletionTime(job->JobEndTime - job->JobStartTime);


        //TODO: update statistics
//        jobEraseList.push_back(job->car->car_spot_number);
        job->car->job = NULL;

}

void JobModel::HandleJobProcessing()
{
  std::list<int> jobEraseList;

  std::map<int, Job*>::iterator it;
  for(it = jobMap.begin(); it != jobMap.end(); it++)
  {
    Job* job = it->second;

    //If the job is still f, then
	if (job->jobStatus == Processing)
	{
      //subtract time from the time left to process
      job->ActiveJobTask->taskProcessingTimeLeft -= _configuration.TimeStep;

      //If the job is no longer processing
      if (job->ActiveJobTask->taskProcessingTimeLeft <= 0)
	  {
        SetActiveTaskComplete(job);
		StartNextJobTask(job);

//        if (job->jobStatus == Complete)
//        {
            //jobEraseList.push_back(it->first);
//            addMigrationJobToDataCenter(job, job->car);
//        }
	  }
	}
  }
  /*
  std::list<int>::iterator itList;
  for(itList = jobEraseList.begin(); itList != jobEraseList.end(); itList++)
  {
    jobMap.erase(*itList);
  }
  */
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
        for(itMJ = job->DataMigrationJobs.begin(); itMJ != job->DataMigrationJobs.end();)
        {
			(*itMJ)->dataLeftToMigrate = (*itMJ)->dataLeftToMigrate - (*itMJ)->currentBandwidthSize;
			if ((*itMJ)->dataLeftToMigrate <=0)
			{
				//**Some statistics should be kept up here.
				//**Update the list of DataMigrationSet vehicles.
				(*itMJ)->carTo->CompletedDataMigrationTasks.push_back(job->ActiveJobTask);
				(*itMJ)->carTo->ActiveDataMigrationTasks.remove(*itMJ);
				job->ActiveJobTask->completedDataMigrationVehicles.push_back((*itMJ)->carTo);
				itMJ = job->DataMigrationJobs.erase(itMJ);
			}
			else
            {
                itMJ++;
            }
		}

		if (job->DataMigrationJobs.empty())
		{
            SetActiveTaskComplete(job);
			StartNextJobTask(job);

//            if (job->jobStatus == Complete)
//            {
                //jobEraseList.push_back(it->first);
//                addMigrationJobToDataCenter(job, job->car);
//            }


//			*_log.info << "Space:" << it->first << " -- Job Complete!" << std::endl;

//			job->jobStatus = Complete;
		    //TODO: update statistics
//			jobEraseList.push_back(it->first);
//            job->car->job = NULL;
		}
	}
  }
  /*
  std::list<int>::iterator itList;
  for(itList = jobEraseList.begin(); itList != jobEraseList.end(); itList++)
  {
    jobMap.erase(*itList);
  }
  */
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

                _statisticsModel.LogSuccessfulVMMigration(_time.getTime() - job->LastVMMigrationStart);

                StartNextJobTask(job);
                //Is it always appropriate to set this to Processing?
                //job->jobStatus = Processing;
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

	//1. Count the number of jobs that are migrating
	//2. Count the number of assigned jobs in the parkinglot.
	//3. Pull off a few more jobs to get the number up to x.

	//int maxJobsInInitialSetup = 1;
	int jobsInInitialSetup = 0;
	int totalJobs = 0;
    std::map<int, Job*>::iterator it;
    for(it = jobMap.begin(); it != jobMap.end(); it++)
    {
      Job* job = it->second;
      if (job->jobStatus == InitialSetup)
      {
        jobsInInitialSetup++;
      }
      totalJobs++;
    }

    CarModel _carModel;
    //While
    // 1. The max jobs in the statua Initial Setup has not been reached, and
    // 2. the total utilization of the vehicles is less than the MaxUtilization
    while (jobsInInitialSetup <= _configuration.MaxJobsInInitialSetup && !jobQueue.empty() && ((double)totalJobs / (double) _carModel.CarsInParkingLot()) * 100 < _configuration.MaxVehicleUtilization)
    {
        Job* jobPtr = jobQueue.top();

        Car* car = _carModel.findCarForAssignment(jobPtr);
        if (car != NULL)
        {
            jobPtr->jobStatus = InitialSetup;
            car->job = jobPtr;
            car->job->car = car;

            /// now that the data is sent from datacenter to the car, we can put it into jobMap
//            *_log.info << "New Job is assigned to car:" << (*it)->carTo->car_spot_number << std::endl;
//            (*it)->jobFrom->car = (*it)->carTo;
//            (*it)->carTo->job_number = (*it)->jobFrom->job_number;
//            (*it)->carTo->job = (*it)->jobFrom;
            jobMap[car->car_spot_number] = jobPtr;
//            cout << "Job " << (*it)->jobFrom->job_number << ", to car to: " << (*it)->carTo->car_spot_number << endl;



            //*_log.info << "New Job is assigning to car: " << car->car_spot_number << std::endl;
            addMigrationJobToDataCenter(jobPtr, car);
            jobQueue.pop();


            if (jobPtr->JobStartTime == -1)
                jobPtr->JobStartTime = _time.getTime();
            jobPtr->JobStartTimeCurrentAttempt = _time.getTime();
        }
        jobsInInitialSetup++;
        totalJobs++;
	}

    //log - jobsInInitialSetup
	//log - totalJobs  (can get the utilization from here)
	//log - size of queue
    _statisticsModel.LogCurrentJobsInInitialSetup(jobsInInitialSetup);
	_statisticsModel.LogCurrentJobsInParkingLot(totalJobs);
	_statisticsModel.LogCurrentJobQueueSize(jobQueue.size());



}

void JobModel::addMigrationJobToDataCenter(Job* jobPtr, Car* car) {

    int dataSize = 0;
    if (jobPtr->jobStatus == InitialSetup )
    {
        dataSize = jobPtr->dataToMigrate + jobPtr->VMsize;
    }
    else
    {
        dataSize = jobPtr->dataToMigrate;
    }
    /// Adding migrationJob to take care of data sending from datacenter to the car
    MigrationJob * migrationJob = new MigrationJob();
    migrationJob->jobFrom = jobPtr;
    migrationJob->carFrom = CarModel::dataCenter;
    migrationJob->carTo = car;
    migrationJob->type = DC;
    migrationJob->totalDataSize = dataSize;
    migrationJob->dataLeftToMigrate = dataSize;
    CarModel::dataCenter->ActiveDataMigrationTasks.push_back(migrationJob);
}

void JobModel::handleMigrationJobsAtDataCenter_ReserveTransaction() {
  NetworkModel _networkModel;
  std::list<MigrationJob*>::iterator it = CarModel::dataCenter->ActiveDataMigrationTasks.begin();
  for(;it != CarModel::dataCenter->ActiveDataMigrationTasks.end(); it++)
  {
      _networkModel.ReserveBandwidth(*it);
  }
}

void JobModel::handleMigrationJobsAtDataCenter_CompleteTransaction() {
    std::list<MigrationJob*>::iterator it = CarModel::dataCenter->ActiveDataMigrationTasks.begin();

    while(it != CarModel::dataCenter->ActiveDataMigrationTasks.end())
    {
        (*it)->dataLeftToMigrate = (*it)->dataLeftToMigrate - (*it)->currentBandwidthSize;
        if ((*it)->dataLeftToMigrate <=0)
        {
            /// sending data from datacenter
            if((*it)->jobFrom->jobStatus == InitialSetup) {
                /// now that the data is sent from datacenter to the car, we can put it into jobMap
//                *_log.info << "New Job is assigned to car:" << (*it)->carTo->car_spot_number << std::endl;
                (*it)->jobFrom->car = (*it)->carTo;
                (*it)->carTo->job_number = (*it)->jobFrom->job_number;
                (*it)->carTo->job = (*it)->jobFrom;
//                jobMap[(*it)->carTo->car_spot_number] = (*it)->jobFrom;
//                cout << "Job " << (*it)->jobFrom->job_number << ", to car to: " << (*it)->carTo->car_spot_number << endl;
                //cin.get();
                StartNextJobTask((*it)->jobFrom);
              /// sending data to datacenter
            } else if ((*it)->jobFrom->jobStatus == FinalMigration) {

                SetJobComplete((*it)->jobFrom);

//                cout << "Job Map size before deletion: " << jobMap.size() << endl;
                jobMap.erase((*it)->carTo->car_spot_number);
//                cout << "Job Map size after deletion: " << jobMap.size() << endl;
                //cin.get();
            }
            CarModel::dataCenter->ActiveDataMigrationTasks.erase(it++);
        } else {
            ++it;
        }
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

      _statisticsModel.LogJobFailed(job);


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

        _statisticsModel.LogFailedVMMigration();

        delete job->VMMigrationJob;
      }

      jobQueue.push(job);
      //delete job;
      //Handle Statistics!
      jobMap.erase(spaceId);

      //Add job back to the jobQueue


      *_log.debug << "Cancelled job in space" << spaceId << "; added back into Queue" << std::endl;
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
