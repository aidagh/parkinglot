//File:         JobModel.hpp
//Description:

#ifndef __JOBMODEL_HPP__
#define __JOBMODEL_HPP__

#include "Logger.hpp"
#include "TimeModel.hpp"
#include "Configuration.hpp"
#include "JobDistributionModel.hpp"
#include "CarModel.hpp"
#include "NetworkModel.hpp"
#include "StatisticsModel.hpp"
#include <map>
#include <queue>

class comparison
{
    bool reversed;
    public:
        comparison(const bool& revparam=false)
        {reversed=revparam;}
    bool operator()(const Job* lhs, const Job* rhs) const
    {
        if(reversed) return lhs->JobArrivalTime > rhs->JobArrivalTime;
        else return lhs->JobArrivalTime < rhs->JobArrivalTime;
    }
};

// using comparison:
typedef std::priority_queue<Job*,std::vector<Job*>,comparison> jobPQ_type;

class JobModel
{
  private:
    Logger _log;
    Configuration _configuration;
    TimeModel _time;
    JobDistributionModel _jobDistributionModel;
	StatisticsModel _statisticsModel;

	//jobQueue contains jobs that could not be assigned to any vehicles
	static jobPQ_type jobQueue;

    //jobMap contains jobs that are assigned to vehicles
	//  jobMap is indexed by parking spot number
	static std::map<int, Job*> jobMap;

	static int numJobs;

	Job* GenerateJob();
	void createNewJob();
	void HandleJobProcessing();
    void SetJobToDataMigrating(Job * job);
    void SetJobToDataProcessing(Job * job);
    void SetJobComplete(Job * job);

    void SetActiveTaskComplete(Job * job);
    void StartNextJobTask(Job * job);

	//Due to the congestion Model the HandleJobDataMigration and HandleJobVMMigration must be handled in two parts.
	//First the network space must be allocated.
	//Once all the Data and VM jobs have been allocated in the network, the available bandwidth will be determined and the Jobs can be updated.
	void HandleJobDataMigration_ReserveTransaction();
    void HandleJobDataMigration_CompleteTransaction();

    void HandleJobVMMigration_ReserveTransaction();
    void HandleJobVMMigration_CompleteTransaction();

    void handleMigrationJobsAtDataCenter_ReserveTransaction();
    void handleMigrationJobsAtDataCenter_CompleteTransaction();
    void addMigrationJobToDataCenter(Job* jobPtr, Car* car);

	void HandleIncomingJobs();
    void HandleCompletedJobs();
    void UpdateJobStats();

  public:
    void Initialize();
	void HandleJobs();

	void CancelJob(int);
	void SetupVMMigration(Car* leavingCar, Car* carToMigrateTo);

};


#endif
