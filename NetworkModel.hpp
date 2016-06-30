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
#include <map>

using namespace std;

class NetworkModel
{
  private:
    Logger _log;
    Configuration _configuration;
    map<int, int> migrations_in_cluster;
    map<int, double> bandwithAllocationMap;
    static list<MigrationJob*> migrationJobList;
    double bandwidthPerMin;
    TimeModel _time;
//    CarModel _carModel;
//	  JobModel _jobModel;
	StatisticsModel _statisticsModel;

    static int lastCongestionDataUpdate;
    void resetMigrationMap();
    void updateCongestionData();

  public:
    NetworkModel();
    void Initialize();
	void ReserveBandwidth(MigrationJob* migrationJob);
	void Allocate();
};



#endif
