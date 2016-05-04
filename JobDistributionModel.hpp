//File:         JobDistributionModel.hpp
//Description:  

#include "TimeModel.hpp"
#include "Random.hpp"
#include "Configuration.hpp"

#ifndef __JOBDISTRIBUTIONMODEL_HPP__
#define __JOBDISTRIBUTIONMODEL_HPP__

class JobDistributionModel
{
  private: 
    Configuration _configuration;
    Random _random;
    TimeModel _time;  
    static int NextArrival;
    static int NextJobLength;
	static int NextVMSize;

	
  public: 
    int getNextArrival();
    int getNextJobLength();    
	int getNextVMSize();
	double getNextJobDataToMigrate();
    int generateNext();
};

int JobDistributionModel::NextArrival = 0;
int JobDistributionModel::NextJobLength = 0;
int JobDistributionModel::NextVMSize = 0;

#endif