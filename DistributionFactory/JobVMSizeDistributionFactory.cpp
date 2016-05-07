//File:         JobVMSizeDistributionFactory.cpp
//Description:  

#include "JobVMSizeDistributionFactory.hpp"

class NormalJobVMSize: public JobVMSizeDistributionFactory
{
	private: 
	std::default_random_engine generatorJobVMSize;
	std::normal_distribution<double> * JobVMSizeNormalDistribution;
	
	
	public:
		void Initialize();
		int getNext();
	
};

void NormalJobVMSize::Initialize()
{
	Configuration _configuration;	
	JobVMSizeNormalDistribution = new std::normal_distribution<double>(_configuration.JobVMSize_Normal_Mean, _configuration.JobVMSize_Normal_STDev);
}

int NormalJobVMSize::getNext()
{
	return (*JobVMSizeNormalDistribution)(generatorJobVMSize);
}


class StaticJobVMSize: public JobVMSizeDistributionFactory
{
	private: 
	    int staticValue;
	public:
		void Initialize();
		int getNext();
	
};

void StaticJobVMSize::Initialize()
{
	Configuration _configuration;	
	staticValue = _configuration.JobVMSize_Static_Value;
}

int StaticJobVMSize::getNext()
{
	return staticValue;
}

JobVMSizeDistributionFactory *JobVMSizeDistributionFactory::make_JobVMSizeDistribution(DistributionType distribution)
{ 
	if (distribution == Static)
		return new StaticJobVMSize;
	if (distribution == Normal)
		return new NormalJobVMSize;
}
