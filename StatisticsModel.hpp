//File:         StatisticsModel.cpp
//Description:

#ifndef __STATISTICSMODEL_HPP__
#define __STATISTICSMODEL_HPP__

#include "Logger.hpp"
#include <list>

class StatisticsModel
{
  private:
    static Logger _log;

    static int cars_arrived;
    static int cars_departed;
    static int jobs_total;
    static int jobs_completed;
    static int jobs_failed;
    static int count_failed_migrate_vm;
    static int count_success_migrate_vm;

    static std::list<int> jobCompletionTimes;


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
    static void LogJobFailed();
	static void LogSuccessfulVMMigration();
	static void LogFailedVMMigration();
	static void LogJobCompletionTime(int);

	static void PrintResults();
};


#endif
