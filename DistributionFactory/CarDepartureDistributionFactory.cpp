//File:         CarDepartureDistributionFactory.cpp
//Description:

#include <random>
#include "../Configuration.hpp"
#include "CarDepartureDistributionFactory.hpp"

class ExponentialDeparture: public CarDepartureDistributionFactory
{
	private:
        static std::default_random_engine generatorDeparture;
        static std::exponential_distribution<double> * DepartureExponentialDistribution;


	public:
		void Initialize();
		double getNext();

};


std::default_random_engine ExponentialDeparture::generatorDeparture;
std::exponential_distribution<double> * ExponentialDeparture::DepartureExponentialDistribution;

void ExponentialDeparture::Initialize()
{
	Configuration _configuration;
    generatorDeparture = std::default_random_engine(_configuration.Seed);
	DepartureExponentialDistribution = new std::exponential_distribution<double>(1/_configuration.CarDeparture_Exponential_Mean);
}

double ExponentialDeparture::getNext()
{
	return (*DepartureExponentialDistribution)(generatorDeparture);
}


class StaticDeparture: public CarDepartureDistributionFactory
{
	private:
	    double staticValue;
	public:
		void Initialize();
		double getNext();

};

void StaticDeparture::Initialize()
{
	Configuration _configuration;
	staticValue = _configuration.CarDeparture_Static_Value;
}

double StaticDeparture::getNext()
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
