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


class CarArrivalDistributionFactory
{
	public:
	    static CarArrivalDistributionFactory *make_CarArrivalDistribution(int choice);
		virtual void Initialize() = 0;  //=0 because we have to declare some function;
		virtual int getNext() = 0;      //=0 because we have to declare some function;
	
};

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








void CarResidencyDistributionModel::Initialize()
{
  *_log.trace << "Initializing CarResidencyDistributionModel" << std::endl;
	
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
  
  NextDeparture = NextArrival + 40;
  

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

