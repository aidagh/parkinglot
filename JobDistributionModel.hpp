//File:         JobDistributionModel.hpp
//Description:

#include "TimeModel.hpp"
#include "Configuration.hpp"
#include "Logger.hpp"

#include "DistributionFactory/JobArrivalDistributionFactory.hpp"
#include "DistributionFactory/JobLengthDistributionFactory.hpp"
#include "DistributionFactory/JobVMSizeDistributionFactory.hpp"
#include "DistributionFactory/JobDataSizeDistributionFactory.hpp"

#ifndef __JOBDISTRIBUTIONMODEL_HPP__
#define __JOBDISTRIBUTIONMODEL_HPP__

class JobDistributionModel
{
  private:
    Configuration _configuration;
    Logger _log;
    TimeModel _time;

    static int NextArrival;
    static int NextJobLength;
	static int NextVMSize;
	static int NextDataSize;

	static JobArrivalDistributionFactory * JobArrivalDistribution;
	static JobLengthDistributionFactory * JobLengthDistribution;
	static JobVMSizeDistributionFactory * JobVMSizeDistribution;
	static JobDataSizeDistributionFactory * JobDataSizeDistribution;

  public:
    void Initialize();
    int getNextArrival();
    int getNextJobLength();
	int getNextVMSize();
	int getNextDataSize();
    void generateNext();
};

#endif
