//File:         CarDepartureDistributionFactory.cpp
//Description:  

#include "CarDepartureDistributionFactory.hpp"

class ExponentialDeparture: public CarDepartureDistributionFactory
{
	private: 
	std::default_random_engine generatorDeparture;
	std::exponential_distribution<double> * DepartureExponentialDistribution;
	
	
	public:
		void Initialize();
		int getNext();
	
};

void ExponentialDeparture::Initialize()
{
	Configuration _configuration;	
	DepartureExponentialDistribution = new std::exponential_distribution<double>(_configuration.CarDeparture_Exponential_Lambda);
}

int ExponentialDeparture::getNext()
{
	return (*DepartureExponentialDistribution)(generatorDeparture);
}


class StaticDeparture: public CarDepartureDistributionFactory
{
	private: 
	    int staticValue;
	public:
		void Initialize();
		int getNext();
	
};

void StaticDeparture::Initialize()
{
	Configuration _configuration;	
	staticValue = _configuration.CarDeparture_Static_Value;
}

int StaticDeparture::getNext()
{
	return staticValue;
}

CarDepartureDistributionFactory *CarDepartureDistributionFactory::make_CarDepartureDistribution(int choice)
{ 
	if (choice == 0)
		return new StaticDeparture;
	if (choice == 1)
		return new ExponentialDeparture;
}
