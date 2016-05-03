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

#include <random>
#include "Logger.hpp"
#include "TimeModel.hpp"
#include "Random.hpp"
#include "Configuration.hpp"


#ifndef __CARRESIDENCYDISTRIBUTIONMODEL_HPP__
#define __CARRESIDENCYDISTRIBUTIONMODEL_HPP__

class CarArrivalDistributionFactory;

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
	
  public: 
    void Initialize();
    int getNextArrival();
	int getNextDeparture();
    int generateNext();
    
};

int CarResidencyDistributionModel::NextArrival = 0;
int CarResidencyDistributionModel::NextDeparture = 0;
CarArrivalDistributionFactory* CarResidencyDistributionModel::CarArrivalDistribution = NULL;

#endif