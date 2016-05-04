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

#include "CarArrivalDistributionFactory.hpp"

class PoissonArrival: public CarArrivalDistributionFactory
{
	private: 
	std::default_random_engine generatorArrival;
	std::poisson_distribution<int> * ArrivalPoissonDistribution;
	
	
	public:
		void Initialize();
		int getNext();
	
};

void PoissonArrival::Initialize()
{
	Configuration _configuration;	
	ArrivalPoissonDistribution = new std::poisson_distribution<int>(_configuration.CarArrival_Poisson_Lambda);
}

int PoissonArrival::getNext()
{
	return (*ArrivalPoissonDistribution)(generatorArrival);
}


class StaticArrival: public CarArrivalDistributionFactory
{
	private: 
	    int staticValue;
	public:
		void Initialize();
		int getNext();
	
};

void StaticArrival::Initialize()
{
	Configuration _configuration;	
	staticValue = _configuration.CarArrival_Static_Value;
}

int StaticArrival::getNext()
{
	return staticValue;
}

CarArrivalDistributionFactory *CarArrivalDistributionFactory::make_CarArrivalDistribution(int choice)
{ 
	if (choice == 0)
		return new StaticArrival;
	if (choice == 1)
		return new PoissonArrival;
}
