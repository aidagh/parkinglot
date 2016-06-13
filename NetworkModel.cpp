//File:         NetworkModel.cpp
//Description:

#include "NetworkModel.hpp"

int NetworkModel::lastCongestionDataUpdate = 0;

// calling constructor to initialize the map
NetworkModel::NetworkModel() {
    for(int i = 1; i <= 64; ++i) {
        migrations_in_cluster.insert(make_pair(i, 0));
        bandwithAllocationMap.insert(make_pair(i, _configuration.BandwidthPerMinuteForClusterInMegaBytes));
    }
}

void NetworkModel::Initialize()
{
   bandwidthPerMin =  _configuration.BandwidthPerMinuteForClusterInMegaBytes;
}

void NetworkModel::resetMigrationMap()
{
    for(int i = 1; i <= 64; ++i) {
        migrations_in_cluster[i] = 0;
        bandwithAllocationMap[i] = bandwidthPerMin;
    }
}

void NetworkModel::updateCongestionData()
{
  //This makes sure the congestion data is only update 1 time for every time step.
  if (lastCongestionDataUpdate < _time.getTime())
  {
      // reset the map every time step
      resetMigrationMap();
	  //1. Loop through each of the data migration and VM migrations
	  //2. calculate the number of jobs at each cluster/group/region/data center
	  //3. Evenly distribute the amount of bandwidth between each job at the cluster level
	  //4. Given the distribution of bandwidth at the cluster level, make sure the amount of
	  //   bandwidth is not exceeded at the group, region, datacenter level.
	  std::map<int, Job*>::iterator it;
	  list<MigrationJob*> allMigrationJobs;
	  Job * jobPtr = nullptr;
	  Car* carFrom = nullptr;
	  Car* carTo = nullptr;
	  for(it = JobModel::jobMap.begin(); it != JobModel::jobMap.end(); ++it) {
        //spotNumber = it->first;
        jobPtr = it->second;
        if(jobPtr->jobStatus == DataMigrating) {
            for(list<MigrationJob*>::iterator dataItr = jobPtr->DataMigrationJobs.begin(); dataItr != jobPtr->DataMigrationJobs.end(); ++dataItr) {
                allMigrationJobs.push_back(*dataItr);
                carFrom = (*dataItr)->carFrom;
                carTo = (*dataItr)->carTo;
                migrations_in_cluster[carFrom->car_cluster_number]++;
                migrations_in_cluster[carTo->car_cluster_number]++;
            }
        } else if (jobPtr->jobStatus == VMMigrating) {
                allMigrationJobs.push_back(jobPtr->VMMigrationJob);
                carFrom = jobPtr->VMMigrationJob->carFrom;
                carTo = jobPtr->VMMigrationJob->carTo;
                migrations_in_cluster[carFrom->car_cluster_number]++;
                migrations_in_cluster[carTo->car_cluster_number]++;
        }
         carFrom = nullptr;
         carTo = nullptr;
	  }
      map<int, int>::iterator mapItr = migrations_in_cluster.begin();

      while(mapItr != migrations_in_cluster.end()) {
          if(mapItr->second != 0) bandwithAllocationMap[mapItr->first] =
                _configuration.BandwidthPerMinuteForClusterInMegaBytes / (double) mapItr->second;
          ++mapItr;
      }
      double bandWidth = 0;
      for(list<MigrationJob*>::iterator it = allMigrationJobs.begin(); it != allMigrationJobs.end(); ++it) {
            carFrom = (*it)->carFrom;
            carTo = (*it)->carTo;
            if(carFrom->car_cluster_number != carTo->car_cluster_number) {
                bandWidth = bandwithAllocationMap[carFrom->car_cluster_number]
                                < bandwithAllocationMap[carTo->car_cluster_number]
                                ? bandwithAllocationMap[carFrom->car_cluster_number]
                                : bandwithAllocationMap[carTo->car_cluster_number];
                (*it)->currentBandwidthSize = bandWidth;
            } else if (carFrom->car_cluster_number == carTo->car_cluster_number) {
                (*it)->currentBandwidthSize = 2 * bandwithAllocationMap[(*it)->carFrom->car_cluster_number];
            }
            carFrom = nullptr;
            carTo = nullptr;

      }
      lastCongestionDataUpdate = _time.getTime();

  }

}

void NetworkModel::ReserveBandwidth(MigrationJob* migrationJob)
{
	//Update the congestion data to keep track of a message going from migrationJob->carFrom to migrationJob->carTo.
	//The migrationJob->type marks the data as "Data" or "VM".  This can be used to determine a priority for the message


	//This will hardcode the bandwidth to 1.  This is done for testing purposes only.  This
	//code should be removed when replaced with the proper congestion model.
	migrationJob->currentBandwidthSize = 1;
}

void NetworkModel::Allocate()
{
    updateCongestionData();
	//Calculate how much bandwidth can be allocated to each migrationJob.
	//Loop through each of the migrationJobs and update the migrationJob->currentBandwidthSize with the available bandwidth for that job.

}

