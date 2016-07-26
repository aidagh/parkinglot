//File:         StatisticsModel.cpp
//Description:

#ifndef __STATISTICSMODEL_HPP__
#define __STATISTICSMODEL_HPP__

#include "Logger.hpp"
#include "ResultsLogger.hpp"
#include "Job.hpp"
#include <list>

class Job;

class StatisticsModel
{
  private:
    static Logger _log;
    static ResultsLogger _results;

    static int cars_arrived;
    static int cars_departed;
    static int jobs_total;
    static int jobs_completed;
    static int jobs_failed;
    static int count_failed_migrate_vm;
    static int count_success_migrate_vm;


    static std::list<int> jobCompletionTimes;
    static double average_job_completion_time;

    static std::list<int> interJobFailureTimes;
    static double MTTF;

    static std::list<int> successfulVMMigrationTimes;
    static double average_successful_VM_Migration_time;
//    static std::list<int> failedVMMigrationTimes;
//    static double average_job_completion_time;

    static std::list<int> jobsInInitialSetup;
    static double average_jobs_in_initial_setup;

    static std::list<int> jobsInParkingLot;
    static double average_jobs_in_parking_lot;

    static std::list<int> jobQueueSize;
    static double average_job_queue_size;

    static std::list<int> carsInParkingLot;
    static double average_cars_in_parking_lot;

    static double getAverageForList(std::list<int> * values);
    static void setAverageJobCompletionTime();
    static void setAverageSuccessfulVMMigrationTime();
    static void setMTTF();
    static void setAverageJobsInInitialSetup();
    static void setAverageJobsInParkingLot();
    static void setAverageJobQueueSize();
    static void setAverageCarsInParkingLot();

    //A list of any possible statistic that we can think of
	//jobs queued
	//jobs taken immediately
	//avg job duration
	//avg time in queue
	//avg job length
	//avg job data backup time
	//avg job completion ( start to finish )
	//avg job completion w/queue time
	//avg cars in parking lot
	//avg cars busy
	//failed jobs
	//total number migrations
	//number successful migrations
	//number failed migrations

  //Update these Log methods to include more data about what is going on.
  public:

    static void Initialize();

    static void LogCarArrived();
    static void LogCarDeparted();
    static void LogJobCompleted();
    static void LogJobFailed(Job* job);
	static void LogSuccessfulVMMigration(int VMmigrationLength);
	static void LogFailedVMMigration();
	static void LogJobCompletionTime(int);

	static void LogCurrentJobsInInitialSetup(int);
	static void LogCurrentJobsInParkingLot(int);
	static void LogCurrentJobQueueSize(int);

	static void LogCurrentCarsInParkingLot(int);


	static void PrintResults();
    static void WriteResults();

};


#endif
