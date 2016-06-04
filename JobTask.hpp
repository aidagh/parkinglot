//File:         JobTask.hpp
//Description:

#ifndef __JOBTASK_HPP__
#define __JOBTASK_HPP__

#include <fstream>
#include <list>
#include "Job.hpp"
//#include "MigrationJob.hpp"

class Job;

enum JobTaskStatus
{
	Task_NotStarted,
	Task_Processing,
	Task_Complete
};

enum JobTaskType
{
	Task_Process,
	Task_DataMigrate
};


// This class stores information about the job tasks.
class JobTask
{
  public:
	Job * job;
	JobTaskType taskType;

	int taskProcessingTime;
	int taskProcessingTimeLeft;

    int taskDataToMigrate;


	JobTaskStatus jobTaskStatus;




//	int dataToMigrate;		  //In Megabytes

	//A list of Data migration jobs for the job that are currently active
//    std::list<MigrationJob*> DataMigrationJobs;

	//A list of VM migration jobs for the job, there "should" only be 1.
//    MigrationJob* VMMigrationJob;

    JobTask();

    void printJobTaskDetails(bool printChildDetails, std::string tab);
    std::string PrintJobTaskStatus(JobTaskStatus jobTaskStatus);

};

#endif
