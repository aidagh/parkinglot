//File:         VehicleParking.cpp
//Project name: To simulate the datacenter for a vehicle parking lot in an Airport.
//Description:  The goal of the project is to simulate a datacenter implemented on the cars in the parking lot of a medium sized airport.
//              As cars arrive and depart randomly, the challenge facing the implementation of the datacenter is to maintain high availability
//              and reliability in the face of the dynamically changing resources. Tradeoffs will be identified and analyzed and several
//              possible solutions will be contrasted. The project is deliberately open ended, allowing each student to add performance-enhancing
//              "bells and whistles".
//Author1:      Aida Ghazizadeh
//Email:        aghaziza@cs.odu.edu
//Author2:      Srinivas Havanur
//Email:        shavanur@cs.odu.edu
//Submitted to: Dr. Stephen Olariu
//Submitted on: 04 December 2015
//Language:     C++

#ifndef __STATISTICSMODEL_HPP__
#define __STATISTICSMODEL_HPP__


class StatisticsModel
{
  private:
    static int jobs_completed;
    static int count_migrated_successfully;
    static int count_failed_to_migrate;


  //Update these Log methods to include more data about what is going on.
  public:
    void LogJobCompleted();
	void LogSuccessfulMigration();
	void LogFailedMigration();
};

int StatisticsModel::jobs_completed = 0;
int StatisticsModel::count_migrated_successfully = 0;
int StatisticsModel::count_failed_to_migrate = 0;

#endif