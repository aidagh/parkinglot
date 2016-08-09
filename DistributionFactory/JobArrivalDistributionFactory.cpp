//File:         JobArrivalDistributionFactory.cpp
//Description:

#include <random>
#include "../Configuration.hpp"
#include "JobArrivalDistributionFactory.hpp"

class PoissonJobArrival: public JobArrivalDistributionFactory
{
	private:
        static std::default_random_engine generatorArrival;
        static std::poisson_distribution<int> * ArrivalPoissonDistribution;


	public:
		void Initialize();
		double getNext();

};

std::default_random_engine PoissonJobArrival::generatorArrival;
std::poisson_distribution<int> * PoissonJobArrival::ArrivalPoissonDistribution;

void PoissonJobArrival::Initialize()
{
	Configuration _configuration;
    generatorArrival = std::default_random_engine(_configuration.Seed);
	ArrivalPoissonDistribution = new std::poisson_distribution<int>(_configuration.JobArrival_Poisson_Lambda);
}

double PoissonJobArrival::getNext()
{
	return (*ArrivalPoissonDistribution)(generatorArrival);
}


class StaticJobArrival: public JobArrivalDistributionFactory
{
	private:
	    double staticValue;
	public:
		void Initialize();
		double getNext();

};

void StaticJobArrival::Initialize()
{
	Configuration _configuration;
	staticValue = _configuration.JobArrival_Static_Value;
}

double StaticJobArrival::getNext()
{
	return staticValue;
}

JobArrivalDistributionFactory *JobArrivalDistributionFactory::make_JobArrivalDistribution(DistributionType distribution)
{
	if (distribution == Static)
		return new StaticJobArrival;
	if (distribution == Poisson)
		return new PoissonJobArrival;

    //Default to Static
    return new StaticJobArrival;

}
