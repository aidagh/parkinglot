//File:         CarArrivalDistributionFactory.cpp
//Description:

#include <random>
#include "../Configuration.hpp"
#include "CarArrivalDistributionFactory.hpp"

class PoissonArrival: public CarArrivalDistributionFactory
{
	private:
        static std::default_random_engine generatorArrival;
        static std::poisson_distribution<int> * ArrivalPoissonDistribution;

	public:
		void Initialize();
		double getNext();

};

std::default_random_engine PoissonArrival::generatorArrival;
std::poisson_distribution<int> * PoissonArrival::ArrivalPoissonDistribution;

void PoissonArrival::Initialize()
{
	Configuration _configuration;
    generatorArrival = std::default_random_engine(_configuration.Seed);
	ArrivalPoissonDistribution = new std::poisson_distribution<int>(_configuration.CarArrival_Poisson_Lambda * 1000);
}

double PoissonArrival::getNext()
{
	return (*ArrivalPoissonDistribution)(generatorArrival) / 1000;
}



class StaticArrival: public CarArrivalDistributionFactory
{
	private:
	    double staticValue;
	public:
		void Initialize();
		double getNext();

};

void StaticArrival::Initialize()
{
	Configuration _configuration;
	staticValue = _configuration.CarArrival_Static_Value;
}

double StaticArrival::getNext()
{
	return staticValue;
}

CarArrivalDistributionFactory *CarArrivalDistributionFactory::make_CarArrivalDistribution(DistributionType distribution)
{
	if (distribution == Static)
		return new StaticArrival;
	if (distribution == Poisson)
		return new PoissonArrival;

    //Default to Static
    return new StaticArrival;
}
