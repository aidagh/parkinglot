//File:         CarModel.hpp
//Description:

#ifndef __CARMODEL_HPP__
#define __CARMODEL_HPP__

#include "Logger.hpp"
#include "TimeModel.hpp"
#include "Random.hpp"
#include "Configuration.hpp"
#include "CarResidencyDistributionModel.hpp"
#include "StatisticsModel.hpp"
#include "Job.hpp"
#include "JobModel.hpp"

#include <map>
#include <list>

class CarModel
{
  private:
    Logger _log;
	Configuration _configuration;
    TimeModel _time;
    StatisticsModel _statisticsModel;
	CarResidencyDistributionModel _carResidencyDistributionModel;

    //carmap is indexed by parking spot number
	static std::map<int, Car*> carmap;
    static std::list<int> emptySpaces;

	//This is used to override some parts of CreateNewCar during the initialize phase.
	static bool initializing;


	void createNewCar();
	Car * GetVMMigrationToVehicle(Car* FromCar);
	void handleVehicleDepartingNOW();
	void handleVehicleDepartingSOON();
    void HandleDepartingVehicles();
	void HandleIncomingVehicles();

  public:
    static Car* dataCenter;
    void Initialize();

	Car* AssignJob(Job* job);
	Car* findCarForAssignment(Job* job);
	std::list<Car*> AssignDataMigrationCars(Job* job);

	void PrintVehicleInfo();
	int getClusterNumber(int);
	int getRegionNumber(int);
	int getGroupNumber(int);

	void HandleCars();
};

#endif
