//File:         JobModel.hpp
//Description:  


#ifndef __JOBMODEL_HPP__
#define __JOBMODEL_HPP__

#include "Logger.hpp"
#include "TimeModel.hpp"
#include "Configuration.hpp"
#include "JobDistributionModel.hpp"
#include "CarModel.hpp"
#include "StatisticsModel.hpp"
#include <map>
#include <queue>


class JobModel
{
  private: 
    Logger _log;
    Configuration _configuration;
//    Random _random;
    TimeModel _time;  
    JobDistributionModel _jobDistributionModel;
//    CarModel _carModel;
	StatisticsModel _statisticsModel;

    //jobMap contains jobs that are assigned to vehicles
	//  jobMap is indexed by parking spot number
	static std::map<int, Job*> jobMap;  
    
	//jobQueue contains jobs that could not be assigned to any vehicles
	static std::queue<Job*> jobQueue;
	
	static int numJobs;
	
	Job* GenerateJob();
	void createNewJob();
	
  public: 
    void Initialize();
	void HandleJobProcessing();
    void HandleJobDataMigration();
    void HandleJobVMMigration();
	void HandleIncomingJobs();
    void HandleCompletedJobs();
	
	void CancelJob(int);
	void SetupVMMigration(Car* leavingCar, Car* carToMigrateTo);
	
};

std::map<int, Job*> JobModel::jobMap;
std::queue<Job*> JobModel::jobQueue;
int JobModel::numJobs = 0;
	


#endif