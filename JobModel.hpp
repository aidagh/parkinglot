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
#include "Configuration.hpp"
#include "JobDistributionModel.hpp"
#include "CarModel.hpp"
#include <map>
#include <queue>

#ifndef __JOBMODEL_HPP__
#define __JOBMODEL_HPP__

class JobModel
{
  private: 
    Configuration _configuration;
//    Random _random;
    TimeModel _time;  
    JobDistributionModel _jobDistributionModel;
    CarModel _carModel;

    //jobMap contains jobs that are assigned to vehicles
	//  jobMap is indexed by parking spot number
	static std::map<int, Job> jobMap;  
    
	//jobQueue contains jobs that could not be assigned to any vehicles
	static std::queue<Job> jobQueue;
	
	static int numJobs;
	
	Job* GenerateJob();
	void createNewJob();
	
  public: 
    void Initialize();
	void HandleJobProcessing();
	void HandleIncomingJobs();
    void HandleCompletedJobs();
};

std::map<int, Job> JobModel::jobMap;
std::queue<Job> JobModel::jobQueue;
int JobModel::numJobs = 0;
	


#endif