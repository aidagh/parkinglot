//File:         VehicleParking.cpp
//Project name: To simulate the datacenter for a vehicle parking lot in an Airport.
//Description:  The goal of the project is to simulate a datacenter implemented on the cars in the parking lot of a medium sized airport.
//              As cars arrive and depart randomly, the challenge facing the implementation of the datacenter is to maintain high availability
//              and reliability in the face of the dynamically changing resources. Tradeoffs will be identified and analyzed and several
//              possible solutions will be contrasted. The project is deliberately open ended, allowing each student to add performance-enhancing
//              "bells and whistles".
//Author1:      Aida Ghazizadeh
//Email:        aghaziza@cs.odu.edu
//Author2:      Srinivas Havanur
//Email:        shavanur@cs.odu.edu
//Submitted to: Dr. Stephen Olariu
//Submitted on: 04 December 2015
//Language:     C++

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