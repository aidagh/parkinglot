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
//	VMMigratingTo,
	VMMigrationComplete,
	DataMigrating,
	Complete


};


// This class stores information about the jobs.
class Job
{
  public:
    //car number that the job belongs to
//	int car_number;
	Car * car;
    int job_number;
    double VM_size;
 //   double VM_migration_remained;
    //bool completed;

	//meaning this job was assigned or not assigned to a car
	JobStatus jobStatus;
//	bool assigned;
//	bool jobProcessingComplete;
//	bool jobComplete;
//	bool jobMigratingFrom;
//	bool jobMigratingTo;


	int jobSize;              //In Minutes
	int jobSizeLeftToProcess; //Starts at jobSize and is subtracted each minute.

	int dataToMigrate;		  //In Megabytes
//	int dataLeftToMigrate;    //Starts at dataToMigrate and is subtracted by available bandwidth each minute

	Car* MigrateToCar;
	Car* MigrateFromCar;
	Job* MigrateToJob;
	Job* MigrateFromJob;


	//A list of Data migration jobs for the job that are currently active
    std::list<MigrationJob*> DataMigrationJobs;

	//A list of VM migration jobs for the job
    std::list<MigrationJob*> VMMigrationJobs;

    //A list of vehicles that are in the latest current DataMigrationSet
	//std::list<int> DataMigrationSet;


//    //double job_duration;  // in minute
//    double data_this_job_will_produce;
//    double data_storage_time;
//    //double job_duration_remained;
//    int data1_car_number;
//    std::string replicated_data;
//    int data2_car_number;
//    int data3_car_number;
//    int data_replication_time_to_same_cluster;
//    int data_replication_time_to_same_region;
//    int migrated_successfully; // 2 for success and 3 for fail
//    bool job_flag_start_migration;
//    bool job_flag_end_migration;
//    int car_num_migration_to;


    Job();

    void printJobDetails(bool printChildDetails, std::string tab);
    std::string PrintJobStatus(JobStatus jobStatus);
    //void display_job_information(std::ofstream& outFile);
    //void calculate_VM_size();
    //void calculate_job_duration();

};



#endif
