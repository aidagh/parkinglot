//File:         JobLengthDistributionFactory.cpp
//Description:  

#include "JobLengthDistributionFactory.hpp"

class NormalJobLength: public JobLengthDistributionFactory
{
	private: 
	std::default_random_engine generatorJobLength;
	std::normal_distribution<double> * JobLengthNormalDistribution;
	
	
	public:
		void Initialize();
		int getNext();
	
};

void NormalJobLength::Initialize()
{
	Configuration _configuration;	
	JobLengthNormalDistribution = new std::normal_distribution<double>(_configuration.JobLength_Normal_Mean, _configuration.JobLength_Normal_STDev);
}

int NormalJobLength::getNext()
{
	return (*JobLengthNormalDistribution)(generatorJobLength);
}


class StaticJobLength: public JobLengthDistributionFactory
{
	private: 
	    int staticValue;
	public:
		void Initialize();
		int getNext();
	
};

void StaticJobLength::Initialize()
{
	Configuration _configuration;	
	staticValue = _configuration.JobLength_Static_Value;
}

int StaticJobLength::getNext()
{
	return staticValue;
}

JobLengthDistributionFactory *JobLengthDistributionFactory::make_JobLengthDistribution(DistributionType distribution)
{ 
	if (distribution == Static)
		return new StaticJobLength;
	if (distribution == Normal)
		return new NormalJobLength;
}
