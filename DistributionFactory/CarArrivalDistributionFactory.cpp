//File:         CarArrivalDistributionFactory.cpp
//Description:

#include <random>
#include "../Configuration.hpp"
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

CarArrivalDistributionFactory *CarArrivalDistributionFactory::make_CarArrivalDistribution(DistributionType distribution)
{
	if (distribution == Static)
		return new StaticArrival;
	if (distribution == Poisson)
		return new PoissonArrival;
}
