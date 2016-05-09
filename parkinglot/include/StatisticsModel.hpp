//File:         StatisticsModel.cpp
//Description:

#ifndef __STATISTICSMODEL_HPP__
#define __STATISTICSMODEL_HPP__


class StatisticsModel
{
  private:
    static int jobs_completed;
    static int count_migrated_successfully;
    static int count_failed_to_migrate;


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
    void LogJobCompleted();
	void LogSuccessfulMigration();
	void LogFailedMigration();

	StatisticsModel();
    virtual ~StatisticsModel();
};

int StatisticsModel::jobs_completed = 0;
int StatisticsModel::count_migrated_successfully = 0;
int StatisticsModel::count_failed_to_migrate = 0;

#endif
