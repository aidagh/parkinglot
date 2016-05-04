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

#include "CarResidencyDistributionModel.hpp"


void CarResidencyDistributionModel::Initialize()
{
  *_log.trace << "Initializing CarResidencyDistributionModel - Car Arrival" << std::endl;
	
  if (_configuration.CarArrival_FromFile)
  {
	  //Use pre-existing file
	  *_log.trace << "   From File" << std::endl;
	
  }
  else if (_configuration.CarArrival_Static)
  {
	  //CarResidency_Static_Hours;   
      CarArrivalDistribution = CarArrivalDistributionFactory::make_CarArrivalDistribution(0);  
	  CarArrivalDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.CarArrival_Poisson)
  {
    CarArrivalDistribution = CarArrivalDistributionFactory::make_CarArrivalDistribution(1);  
	CarArrivalDistribution->Initialize();
    *_log.trace << "   Poisson" << std::endl;
  }

  
  
  *_log.trace << "Initializing CarResidencyDistributionModel - Car Departure" << std::endl;
	
//  if (_configuration.CarArrival_FromFile)
//  {
//	  //Use pre-existing file
//	  *_log.trace << "   From File" << std::endl;
//	
//  } 
//  else 
	  if (_configuration.CarDeparture_Static)
  {
	  //CarResidency_Static_Hours;   
      CarDepartureDistribution = CarDepartureDistributionFactory::make_CarDepartureDistribution(0);  
	  CarDepartureDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.CarDeparture_Exponential)
  {
    CarDepartureDistribution = CarDepartureDistributionFactory::make_CarDepartureDistribution(1);  
	CarDepartureDistribution->Initialize();
    *_log.trace << "   Departure" << std::endl;
  }

	
}

int CarResidencyDistributionModel::getNextArrival()
{
	if (NextArrival == 0)
	{
		generateNext();
	}	
	return NextArrival;
}


int CarResidencyDistributionModel::getNextDeparture()
{
	if (NextDeparture == 0)
	{
		generateNext();
	}
	return NextDeparture;
}

int CarResidencyDistributionModel::generateNext()
{
  *_log.trace << "CarResidencyDistributionModel.generateNext()" << std::endl;
  //This needs to be updated to work based on the configuration
  NextArrival = _time.getTime() + CarArrivalDistribution->getNext();
  
  NextDeparture = NextArrival + CarDepartureDistribution->getNext();
  

  //Test for Distributions
//  std::default_random_engine generator;
//  std::poisson_distribution<int> distribution(4.1);
//  int a = distribution(generator);
  
  /*
  if (_configuration.CarResidency_FromFile)
  {
	  //Use pre-existing file
  }
  else if (_configuration.CarResidency_Static)
  {
	  //CarResidency_Static_Hours;   
  }
  else if (_configuration.CarResidency_Exponential)
  {
	//_configuration.CarResidency_Exponential_Lambda;  
  }
  */
}

