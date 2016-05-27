//File:         NetworkModel.cpp
//Description:

#include "NetworkModel.hpp"

int NetworkModel::lastCongestionDataUpdate = 0;

void NetworkModel::Initialize()
{
   //double bandWidthPerSecond =  _configuration.BandwidthPerSecondForCluster;
}

void NetworkModel::updateCongestionData()
{
  //This makes sure the congestion data is only update 1 time for every time step.
  if (lastCongestionDataUpdate < _time.getTime())
  {
	  //1. Loop through each of the data migration and VM migrations
	  //2. calculate the number of jobs at each cluster/group/region/data center
	  //3. Evenly distribute the amount of bandwidth between each job at the cluster level
	  //4. Given the distribution of bandwidth at the cluster level, make sure the amount of
	  //   bandwidth is not exceeded at the group, region, datacenter level.
	  map<int, int> migrations_in_cluster;
	  std::map<int, Job*>::iterator it;
	  list<Job*> migratingJobs;
	  //int spotNumber = -1;
	  Job * jobPtr = nullptr;
	  for(it = JobModel::jobMap.begin(); it != JobModel::jobMap.end(); ++it) {
        //spotNumber = it->first;
        jobPtr = it->second;
        if(jobPtr->jobStatus == DataMigrating || jobPtr->jobStatus == VMMigrating) {
            migratingJobs.push_back(jobPtr);
           if (migrations_in_cluster.find(jobPtr->car->car_cluster_number) == migrations_in_cluster.end())
            {
                migrations_in_cluster.insert(make_pair(jobPtr->car->car_cluster_number, 1));
            } else {
                migrations_in_cluster[jobPtr->car->car_cluster_number]++;
            }
        }
	  }
      double bandwidthPerSecondForCluster = _configuration.BandwidthPerSecondForCluster;
      map<int, int>::iterator mapItr = migrations_in_cluster.begin();
        while(mapItr != migrations_in_cluster.end()) {
           mapItr->second = bandwidthPerSecondForCluster/ mapItr->second;
          ++mapItr;
        }
      for(list<Job*>::iterator it = migratingJobs.begin(); it != migratingJobs.end(); ++it) {

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

