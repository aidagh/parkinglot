//File:         Job.hpp
//Description:

#ifndef __JOB_HPP__
#define __JOB_HPP__

#include <fstream>
#include <list>
#include "Car.hpp"
#include "MigrationJob.hpp"

class Car;

enum JobStatus
{
	Idle,
	Processing,
	VMMigrating,
	VMMigrationComplete,
	DataMigrating,
	Complete


};


// This class stores information about the jobs.
class Job
{
  public:
	Car * car;
    int job_number;
    double VMsize;

	JobStatus jobStatus;

	int jobSize;              //In Minutes
	int jobSizeLeftToProcess; //Starts at jobSize and is subtracted each minute.

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
