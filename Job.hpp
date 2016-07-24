//File:         Job.hpp
//Description:

#ifndef __JOB_HPP__
#define __JOB_HPP__

#include <fstream>
#include <list>
#include "Car.hpp"
#include "JobTask.hpp"
#include "MigrationJob.hpp"

class Car;
class JobTask;

enum JobStatus
{
	Idle,
	InitialSetup,
	Processing,
	VMMigrating,
	VMMigrationComplete,
	DataMigrating,
	FinalMigration,
	Complete


};


// This class stores information about the jobs.
class Job
{
  public:
	Car * car;
    int job_number;
    double VMsize;

    //This is the time the job arrives in the queue (the first time)
    int JobArrivalTime;


    //This is the time the job is FIRST started
    int JobStartTime;
    int JobEndTime;

    //This is the time the job was started, not the original assignment.
    //If the job fails, this time will be changed
    int JobStartTimeCurrentAttempt;


    //Used to calculate the length of a VM Migration
    int LastVMMigrationStart;


	JobStatus jobStatus;

	std::list<JobTask*> JobTasks;
    JobTask* ActiveJobTask;


	int jobProcessingTime;              //In Minutes
	int jobProcessingTimeLeft; //Starts at jobProcessingTime and is subtracted each minute.

	int dataToMigrate;		  //In Megabytes

	//A list of Data migration jobs for the job that are currently active
    std::list<MigrationJob*> DataMigrationJobs;

	//A list of VM migration jobs for the job, there "should" only be 1.
    MigrationJob* VMMigrationJob;

    Job();

    void printJobDetails(bool printChildDetails, std::string tab);
    std::string PrintJobStatus(JobStatus jobStatus);

};

#endif
