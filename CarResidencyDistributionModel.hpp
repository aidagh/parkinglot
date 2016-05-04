//File:         CarResidencyDistributionModel.hpp
//Description: 
//
//
//



#ifndef __CARRESIDENCYDISTRIBUTIONMODEL_HPP__
#define __CARRESIDENCYDISTRIBUTIONMODEL_HPP__

#include <random>
#include "Logger.hpp"
#include "TimeModel.hpp"
#include "Random.hpp"
#include "Configuration.hpp"
#include "CarArrivalDistributionFactory.hpp"
#include "CarDepartureDistributionFactory.hpp"

class CarResidencyDistributionModel
{
  private: 
    Logger _log;
    Configuration _configuration;
    Random _random;
    TimeModel _time;  
    static int NextArrival;
	static int NextDeparture;

	
	static CarArrivalDistributionFactory * CarArrivalDistribution;
	static CarDepartureDistributionFactory * CarDepartureDistribution;
	
  public: 
    void Initialize();
    int getNextArrival();
	int getNextDeparture();
    int generateNext();
    
};

int CarResidencyDistributionModel::NextArrival = 0;
int CarResidencyDistributionModel::NextDeparture = 0;
CarArrivalDistributionFactory* CarResidencyDistributionModel::CarArrivalDistribution = NULL;
CarDepartureDistributionFactory* CarResidencyDistributionModel::CarDepartureDistribution = NULL;

#endif