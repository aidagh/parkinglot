//File:         CarDepartureDistributionFactory.cpp
//Description:

#include <random>
#include "../Configuration.hpp"
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

CarDepartureDistributionFactory *CarDepartureDistributionFactory::make_CarDepartureDistribution(DistributionType distribution)
{
	if (distribution == Static)
		return new StaticDeparture;
	if (distribution == Exponential)
		return new ExponentialDeparture;

    //Default to Static
    return new StaticDeparture;

}
