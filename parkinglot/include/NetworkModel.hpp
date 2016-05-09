//File:         NetworkModel.hpp
//Description:


#ifndef __NETWORKMODEL_HPP__
#define __NETWORKMODEL_HPP__

#include "Logger.hpp"
#include "TimeModel.hpp"
#include "Configuration.hpp"
#include "JobDistributionModel.hpp"
#include "CarModel.hpp"
#include "StatisticsModel.hpp"


class NetworkModel
{
  private:
    Logger _log;
    Configuration _configuration;
    TimeModel _time;
//    CarModel _carModel;
//	  JobModel _jobModel;
	StatisticsModel _statisticsModel;

    static int lastCongestionDataUpdate;
    void updateCongestionData();

  public:
    void Initialize();
	void ReserveBandwidth(MigrationJob* migrationJob);
	void Allocate();

	NetworkModel();
    virtual ~NetworkModel();
};

int NetworkModel::lastCongestionDataUpdate = 0;

#endif
