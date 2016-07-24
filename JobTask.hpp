//File:         JobTask.hpp
//Description:


#ifndef __JOBTASK_HPP__
#define __JOBTASK_HPP__

#include <fstream>
#include <list>
#include "Job.hpp"
#include "Car.hpp"
//#include "MigrationJob.hpp"

class Job;
class Car;

enum JobTaskStatus
{
	Task_NotStarted,
	Task_InProgress,
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



	//This list hold the list of vehicles with completed Data Migrations.
	std::list<Car*> completedDataMigrationVehicles;

//	int dataToMigrate;		  //In Megabytes

	//A list of Data migration jobs for the job that are currently active
//    std::list<MigrationJob*> DataMigrationJobs;

	//A list of VM migration jobs for the job, there "should" only be 1.
//    MigrationJob* VMMigrationJob;

    JobTask();

    void printJobTaskDetails(bool printChildDetails, std::string tab);
    std::string PrintJobTaskStatus(JobTaskStatus jobTaskStatus);
    std::string PrintJobTaskType(JobTaskType jobTaskType);

};

#endif
