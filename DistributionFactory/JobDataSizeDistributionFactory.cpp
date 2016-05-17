//File:         JobDataSizeDistributionFactory.cpp
//Description:
#include <random>
#include "../Configuration.hpp"
#include "JobDataSizeDistributionFactory.hpp"

class NormalJobDataSize: public JobDataSizeDistributionFactory
{
	private:
	std::default_random_engine generatorJobDataSize;
	std::normal_distribution<double> * JobDataSizeNormalDistribution;


	public:
		void Initialize();
		int getNext();

};

void NormalJobDataSize::Initialize()
{
	Configuration _configuration;
	JobDataSizeNormalDistribution = new std::normal_distribution<double>(_configuration.JobDataSize_Normal_Mean, _configuration.JobDataSize_Normal_STDev);
}

int NormalJobDataSize::getNext()
{
	return (*JobDataSizeNormalDistribution)(generatorJobDataSize);
}


class StaticJobDataSize: public JobDataSizeDistributionFactory
{
	private:
	    int staticValue;
	public:
		void Initialize();
		int getNext();

};

void StaticJobDataSize::Initialize()
{
	Configuration _configuration;
	staticValue = _configuration.JobDataSize_Static_Value;
}

int StaticJobDataSize::getNext()
{
	return staticValue;
}

JobDataSizeDistributionFactory *JobDataSizeDistributionFactory::make_JobDataSizeDistribution(DistributionType distribution)
{
	if (distribution == Static)
		return new StaticJobDataSize;
	if (distribution == Normal)
		return new NormalJobDataSize;
}
