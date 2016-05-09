//File:         CarResidencyDistributionModel.hpp
//Description: 	Provides random values for the car residency
//	Initialize() - Used to initialize the model with values from configuration
//  GetNextArrival() - Used to get the next random value for the car arrival. (In terms of x time units from now)
//  GetNextDeparture() - Used to get the next random value for the car departure. (In terms of vehicle residency time)
//  GenerateNext() - populate NextArrival and NextDeparture with new random values.


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

    CarResidencyDistributionModel();
    virtual ~CarResidencyDistributionModel();

};

int CarResidencyDistributionModel::NextArrival = 0;
int CarResidencyDistributionModel::NextDeparture = 0;
CarArrivalDistributionFactory* CarResidencyDistributionModel::CarArrivalDistribution = NULL;
CarDepartureDistributionFactory* CarResidencyDistributionModel::CarDepartureDistribution = NULL;

#endif
