//File:         CarModel.hpp
//Description:  

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
    void HandleDepartingVehicles();
	void HandleIncomingVehicles();
	
  public: 
    void Initialize();
	
	Car* AssignJob(Job* job);
	
	int getClusterNumber(int);
	int getRegionNumber(int);
	int getGroupNumber(int);
	
	void HandleCars();
	
};

std::map<int, Car*> CarModel::carmap;
std::list<int> CarModel::emptySpaces; 
bool CarModel::initializing = false;

#endif