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

#ifndef __CARMODEL_HPP__
#define __CARMODEL_HPP__

#include "Logger.hpp"
#include "TimeModel.hpp"
#include "Random.hpp"
#include "Configuration.hpp"
#include "CarResidencyDistributionModel.hpp"
#include "Job.hpp"
#include "JobModel.hpp"

#include <map>
#include <list>

class JobModel;

class CarModel
{
  private: 
    Logger _log;
	Configuration _configuration;
    Random _random;
    TimeModel _time;  
	CarResidencyDistributionModel _carResidencyDistributionModel;
	JobModel _jobModel;
    //carmap is indexed by parking spot number
	static std::map<int, Car*> carmap;  
    static std::list<int> emptySpaces; 
	
	//This is used to override some parts of CreateNewCar during the initialize phase.
	static bool initializing;
	
	
	bool createNewCar();
	Car * GetMigrationToVehicle(Car* FromCar);
	void handleVehicleDepartingNOW();
	void handleVehicleDepartingSOON();
	
  public: 
    void Initialize();
    void HandleDepartingVehicles();
	void HandleIncomingVehicles();
	
	Car* AssignJob(Job* job);
	
	int getClusterNumber(int);
	int getRegionNumber(int);
	int getGroupNumber(int);
	
};

std::map<int, Car*> CarModel::carmap;
std::list<int> CarModel::emptySpaces; 
bool CarModel::initializing = false;

#endif