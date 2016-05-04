//File:         JobArrivalDistributionFactory.cpp
//Description:  

#include "JobArrivalDistributionFactory.hpp"

class PoissonJobArrival: public JobArrivalDistributionFactory
{
	private: 
	std::default_random_engine generatorArrival;
	std::poisson_distribution<int> * ArrivalPoissonDistribution;
	
	
	public:
		void Initialize();
		int getNext();
	
};

void PoissonJobArrival::Initialize()
{
	Configuration _configuration;	
	ArrivalPoissonDistribution = new std::poisson_distribution<int>(_configuration.JobArrival_Poisson_Lambda);
}

int PoissonJobArrival::getNext()
{
	return (*ArrivalPoissonDistribution)(generatorArrival);
}


class StaticJobArrival: public JobArrivalDistributionFactory
{
	private: 
	    int staticValue;
	public:
		void Initialize();
		int getNext();
	
};

void StaticJobArrival::Initialize()
{
	Configuration _configuration;	
	staticValue = _configuration.JobArrival_Static_Value;
}

int StaticJobArrival::getNext()
{
	return staticValue;
}

JobArrivalDistributionFactory *JobArrivalDistributionFactory::make_JobArrivalDistribution(int choice)
{ 
	if (choice == 0)
		return new StaticJobArrival;
	if (choice == 1)
		return new PoissonJobArrival;
}
