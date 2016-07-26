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
#include "ResultsLogger.hpp"
#include <map>

using namespace std;

class NetworkModel
{
  private:
    Logger _log;
    ResultsLogger _results;
    Configuration _configuration;
    /// first = cluster number; second = number of migrations
    map<int, int> migrations_in_cluster;
    /// we evenly distribute bandwidth of each cluster and store it
    /// in a map: first = cluster number, second: bandwidth
    map<int, double> bandwithAllocationMap;
    /// first = group number; second = number of migrations
    map<int, int> migratios_in_group;
    /// we evenly distribute bandwidth of each group and store it
    /// in a map: first = group number, second: bandwidth
    map<int, double> bandwithAllocationMapGroup;
    /// first = region number; second = number of migrations
    map<int, int> migrations_in_region;
    /// we evenly distribute bandwidth of each region and store it
    /// in a map: first = region number, second: bandwidth
    map<int, double> bandwithAllocationMapRegion;
    /// we don't need any map for the data center since there is only one data center
    int migartion_in_datacenter;
    /// this variable is used after the bandwidth is evenly distributed
    double bandwidthAllocationDataCenter;
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
