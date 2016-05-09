//File:         JobDistributionModel.hpp
//Description:

#include "TimeModel.hpp"
#include "Random.hpp"
#include "Configuration.hpp"

#include "JobArrivalDistributionFactory.hpp"
#include "JobLengthDistributionFactory.hpp"
#include "JobVMSizeDistributionFactory.hpp"
#include "Logger.hpp"

#ifndef __JOBDISTRIBUTIONMODEL_HPP__
#define __JOBDISTRIBUTIONMODEL_HPP__

class JobDistributionModel
{
  private:
    Configuration _configuration;
    Logger _log;
	Random _random;
    TimeModel _time;

    static int NextArrival;
    static int NextJobLength;
	static int NextVMSize;

	static JobArrivalDistributionFactory * JobArrivalDistribution;
	static JobLengthDistributionFactory * JobLengthDistribution;
	static JobVMSizeDistributionFactory * JobVMSizeDistribution;

  public:
    void Initialize();
    int getNextArrival();
    int getNextJobLength();
	int getNextVMSize();
	double getNextJobDataToMigrate();
    int generateNext();

    JobDistributionModel();
    virtual ~JobDistributionModel();
};

int JobDistributionModel::NextArrival = 0;
int JobDistributionModel::NextJobLength = 0;
int JobDistributionModel::NextVMSize = 0;

JobArrivalDistributionFactory* JobDistributionModel::JobArrivalDistribution = NULL;
JobLengthDistributionFactory* JobDistributionModel::JobLengthDistribution = NULL;
JobVMSizeDistributionFactory* JobDistributionModel::JobVMSizeDistribution = NULL;
#endif
