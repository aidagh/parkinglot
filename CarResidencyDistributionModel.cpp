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
  //This needs to be updated to work based on the configuration
  NextArrival = _time.getTime() + 10;
  NextDeparture = NextArrival + 1440;
  
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

