//File:         NetworkModel.cpp
//Description:

#include "NetworkModel.hpp"

int NetworkModel::lastCongestionDataUpdate = 0;
list<MigrationJob*> NetworkModel::migrationJobList;

// calling constructor to initialize the map
NetworkModel::NetworkModel() {

}

void NetworkModel::Initialize()
{
   bandwidthPerMin =  _configuration.BandwidthPerMinuteForClusterInMegaBytes;
}

void NetworkModel::resetMigrationMap()
{
    for(int i = 1; i <= 64; ++i) {
        /// initializing the number of jobs in each cluster to zero
        migrations_in_cluster.insert(make_pair(i, 0));
        /// initializing the the bandwidth of each cluster to full value = 75
        bandwithAllocationMap.insert(make_pair(i, _configuration.BandwidthPerMinuteForClusterInMegaBytes));
    }
    for(int i = 1; i <= 16; ++i) {
        migratios_in_group.insert(make_pair(i, 0));
        bandwithAllocationMapGroup.insert(make_pair(i, _configuration.BandwidthPerMinuteForWiredLinksInMegaBytes));
    }
    for(int i = 1; i <= 4; ++i) {
        migrations_in_region.insert(make_pair(i, 0));
        bandwithAllocationMapRegion.insert(make_pair(i, _configuration.BandwidthPerMinuteForWiredLinksInMegaBytes));
    }
    migartion_in_datacenter = 0;
    bandwidthAllocationDataCenter = _configuration.BandwidthPerMinuteForWiredLinksInMegaBytes;
    /*
    for(int i = 1; i <= 64; ++i) {
        migrations_in_cluster[i] = 0;
        bandwithAllocationMap[i] = bandwidthPerMin;
    }*/
}

void NetworkModel::updateCongestionData()
{
  //This makes sure the congestion data is only update 1 time for every time step.
  if (lastCongestionDataUpdate < _time.getTime())
  {
      /// reset the map every time step
      resetMigrationMap();
	  //1. Loop through each of the data migration and VM migrations
	  //2. calculate the number of jobs at each cluster/group/region/data center
	  //3. Evenly distribute the amount of bandwidth between each job at the cluster level
	  //4. Given the distribution of bandwidth at the cluster level, make sure the amount of
	  //   bandwidth is not exceeded at the group, region, datacenter level.
	  //Job * jobPtr = nullptr;
	  Car* carFrom = nullptr;
	  Car* carTo = nullptr;
	  /// loop through all the migrationJobList (static list to store all the migration jobs) to calculate the number of
	  /// jobs in each cluster
	  //cout << "Inside Network Congestion UpdateCongestionData() " << endl;
	  for(list<MigrationJob*>::iterator dataItr = migrationJobList.begin(); dataItr != migrationJobList.end(); ++dataItr) {
	      carFrom = (*dataItr)->carFrom;
          carTo = (*dataItr)->carTo;
          //cout << "\tCar from cluster number: " << carFrom->car_cluster_number << endl;
          //cout << "\tCar TO cluster number: " << carTo->car_cluster_number << endl;
          migrations_in_cluster[carFrom->car_cluster_number]++;
          migrations_in_cluster[carTo->car_cluster_number]++;
          /// if the regions are different, then we know it is going to pass from data center
          /// and each of the regions and groups need to be incremented
          if(carFrom->car_region_number != carTo->car_region_number) {
            migartion_in_datacenter++;
            migrations_in_region[carFrom->car_region_number]++;
            migrations_in_region[carTo->car_region_number]++;
            migratios_in_group[carFrom->car_group_number]++;
            migratios_in_group[carTo->car_group_number]++;
          } else {
              /// else we have different scenarios
              if(carFrom->car_group_number != carTo->car_group_number) {
                /// does not matter if we increment by carTo or carFrom region number, but we have to increment only once
                migrations_in_region[carTo->car_region_number]++;
                /// we increment both groups for carFrom and carTo
                migratios_in_group[carFrom->car_group_number]++;
                migratios_in_group[carTo->car_group_number]++;
              } else if(carFrom->car_group_number == carTo->car_group_number && carFrom->car_cluster_number != carTo->car_cluster_number) {
                  /// does not matter if we increment by carTo or carFrom group number, but we have to increment only once
                    migratios_in_group[carTo->car_group_number]++;
                }

          }
      }
      carFrom = nullptr;
      carTo = nullptr;
      map<int, int>::iterator mapItr = migrations_in_cluster.begin();
      while(mapItr != migrations_in_cluster.end()) {
          /// we loop through the map we just created in order to evenly distribute the bandwidth.
          /// we store the calculated value in bandwithAllocationMap which is mapping bandwidth with cluster number
          if(mapItr->second != 0) bandwithAllocationMap[mapItr->first] =
                _configuration.BandwidthPerMinuteForClusterInMegaBytes / (double) mapItr->second;
          ++mapItr;
      }
      /*
      map<int, double>::iterator mapItr2 = bandwithAllocationMap.begin();
      while(mapItr2 != bandwithAllocationMap.end()) {
          /// we loop through the map we just created in order to evenly distribute the bandwidth.
          /// we store the calculated value in bandwithAllocationMap which is mapping bandwidth with cluster number
          if(mapItr2->second != 0) {
                cout << "cluster number: " << mapItr2->first << ", bandwidth: " << mapItr2->second << endl;
          }
          ++mapItr2;
      }*/

      lastCongestionDataUpdate = _time.getTime();

  }

}

void NetworkModel::ReserveBandwidth(MigrationJob* migrationJob)
{
	//Update the congestion data to keep track of a message going from migrationJob->carFrom to migrationJob->carTo.
	//The migrationJob->type marks the data as "Data" or "VM".  This can be used to determine a priority for the message


	//This will hardcode the bandwidth to 1.  This is done for testing purposes only.  This
	//code should be removed when replaced with the proper congestion model.
	//migrationJob->currentBandwidthSize = 1;
	migrationJobList.push_back(migrationJob);
}

void NetworkModel::Allocate()
{
    updateCongestionData();
    //Calculate how much bandwidth can be allocated to each migrationJob.
	//Loop through each of the migrationJobs and update the migrationJob->currentBandwidthSize with the available bandwidth for that job.

    double bandWidth = 0;
    Car* carFrom = nullptr;
    Car* carTo = nullptr;
    /// we have to loop through the migration jobs again to assign/update the bandwidth to each migration job
    for(list<MigrationJob*>::iterator it = migrationJobList.begin(); it != migrationJobList.end(); ++it) {
        carFrom = (*it)->carFrom;
        carTo = (*it)->carTo;
        /// find out the minimum bandwidth of the two cars and then choose the minimum one
        bandWidth = bandwithAllocationMap[carFrom->car_cluster_number]
                            < bandwithAllocationMap[carTo->car_cluster_number]
                            ? bandwithAllocationMap[carFrom->car_cluster_number]
                            : bandwithAllocationMap[carTo->car_cluster_number];
        /// assign the bandwidth to the migrationJob's currentBandwithSize
        (*it)->currentBandwidthSize = bandWidth;
        /*
        if(carFrom->car_cluster_number != carTo->car_cluster_number) {
            bandWidth = bandwithAllocationMap[carFrom->car_cluster_number]
                            < bandwithAllocationMap[carTo->car_cluster_number]
                            ? bandwithAllocationMap[carFrom->car_cluster_number]
                            : bandwithAllocationMap[carTo->car_cluster_number];
            (*it)->currentBandwidthSize = bandWidth;
        } else if (carFrom->car_cluster_number == carTo->car_cluster_number) {
            (*it)->currentBandwidthSize = 2 * bandwithAllocationMap[(*it)->carFrom->car_cluster_number];
        }
        */
        carFrom = nullptr;
        carTo = nullptr;

    }
    /// clear the migrationJobList to be prepared for the next time step
    migrationJobList.clear();
}

