//File:         CarResidencyDistributionModel.cpp
//Description: 	Provides random values for the car residency

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

