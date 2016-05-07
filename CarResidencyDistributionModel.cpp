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
      CarArrivalDistribution = CarArrivalDistributionFactory::make_CarArrivalDistribution(Static);  
	  CarArrivalDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.CarArrival_Poisson)
  {
    CarArrivalDistribution = CarArrivalDistributionFactory::make_CarArrivalDistribution(Poisson);  
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
      CarDepartureDistribution = CarDepartureDistributionFactory::make_CarDepartureDistribution(Static);  
	  CarDepartureDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.CarDeparture_Exponential)
  {
    CarDepartureDistribution = CarDepartureDistributionFactory::make_CarDepartureDistribution(Exponential);  
	CarDepartureDistribution->Initialize();
    *_log.trace << "   Exponential" << std::endl;
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
  NextArrival = _time.getTime() + CarArrivalDistribution->getNext();
  NextDeparture = NextArrival + CarDepartureDistribution->getNext();
   
}

