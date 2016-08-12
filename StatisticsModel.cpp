//File:         StatisticsModel.hpp
//Description:


#include "StatisticsModel.hpp"
#include "TimeModel.hpp"
#include <list>
int StatisticsModel::cars_arrived = 0;
int StatisticsModel::cars_departed = 0;
int StatisticsModel::jobs_completed = 0;
int StatisticsModel::jobs_failed = 0;
int StatisticsModel::count_failed_migrate_vm = 0;
int StatisticsModel::count_success_migrate_vm = 0;

double StatisticsModel::average_job_completion_time = 0;
double StatisticsModel::MTTF = 0;
double StatisticsModel::average_successful_VM_Migration_time = 0;
double StatisticsModel::average_jobs_in_initial_setup = 0;
double StatisticsModel::average_jobs_in_parking_lot = 0;
double StatisticsModel::average_job_queue_size = 0;
double StatisticsModel::average_cars_in_parking_lot = 0;

double StatisticsModel::average_timeSpentInProcessing = 0;
double StatisticsModel::average_timeSpentInInitialSetup = 0;
double StatisticsModel::average_timeSpentInBackup = 0;
double StatisticsModel::average_timeSpentInFinalization = 0;
double StatisticsModel::average_timeSpentInVMMigration = 0;








std::list<int> StatisticsModel::jobCompletionTimes;
std::list<int> StatisticsModel::interJobFailureTimes;
std::list<int> StatisticsModel::successfulVMMigrationTimes;
std::list<int> StatisticsModel::failedVMMigrationTimes;

std::list<int> StatisticsModel::jobsInInitialSetup;
std::list<int> StatisticsModel::jobsInParkingLot;
std::list<int> StatisticsModel::jobQueueSize;
std::list<int> StatisticsModel::carsInParkingLot;

std::list<int> StatisticsModel::timeSpentInProcessing;
std::list<int> StatisticsModel::timeSpentInInitialSetup;
std::list<int> StatisticsModel::timeSpentInBackup;
std::list<int> StatisticsModel::timeSpentInFinalization;
std::list<int> StatisticsModel::timeSpentInVMMigration;

void StatisticsModel::Initialize()
{
  jobs_completed = 0;
  count_failed_migrate_vm = 0;
  count_success_migrate_vm = 0;
  average_job_completion_time = 0;
  //jobCompletionTimes.clear?
  jobCompletionTimes = std::list<int>();
  interJobFailureTimes = std::list<int>();
  successfulVMMigrationTimes = std::list<int>();
  jobsInInitialSetup = std::list<int>();
  jobsInParkingLot = std::list<int>();
  jobQueueSize =  std::list<int>();
  carsInParkingLot = std::list<int>();

}

void StatisticsModel::LogCarArrived()
{
	cars_arrived++;
}
void StatisticsModel::LogCarDeparted()
{
	cars_departed++;
}
void StatisticsModel::LogJobCompleted()
{
	jobs_completed++;
}
void StatisticsModel::LogJobFailed(Job * job)
{
    TimeModel _time;
    interJobFailureTimes.push_back(_time.getTime() - job->JobStartTimeCurrentAttempt);
	jobs_failed++;
}

void StatisticsModel::LogSuccessfulVMMigration(int VMmigrationLength)
{
    successfulVMMigrationTimes.push_back(VMmigrationLength);
	count_success_migrate_vm++;
}

void StatisticsModel::LogFailedVMMigration(int VMmigrationLength)
{
    failedVMMigrationTimes.push_back(VMmigrationLength);
	count_failed_migrate_vm++;
}


void StatisticsModel::LogJobCompletionTime(int completionTime)
{
  jobCompletionTimes.push_back(completionTime);
}

void StatisticsModel::LogCurrentJobsInInitialSetup(int numJobs)
{
  jobsInInitialSetup.push_back(numJobs);
}
void StatisticsModel::LogCurrentJobsInParkingLot(int numJobs)
{
  jobsInParkingLot.push_back(numJobs);
}
void StatisticsModel::LogCurrentJobQueueSize(int numJobs)
{
  jobQueueSize.push_back(numJobs);
}
void StatisticsModel::LogCurrentCarsInParkingLot(int numCars)
{
  carsInParkingLot.push_back(numCars);
}

void StatisticsModel::LogJobStats(int _timeSpentInProcessing, int _timeSpentInInitialSetup, int _timeSpentInBackup, int _timeSpentInFinalization, int _timeSpentInVMMigration)
{
	timeSpentInProcessing.push_back(_timeSpentInProcessing);
	timeSpentInInitialSetup.push_back(_timeSpentInInitialSetup);
	timeSpentInBackup.push_back(_timeSpentInBackup);
	timeSpentInFinalization.push_back(_timeSpentInFinalization);
	timeSpentInVMMigration.push_back(_timeSpentInVMMigration);
}


double StatisticsModel::getAverageForList(std::list<int> * values)
{
    double totalSum = 0;
    int count = 0;

    std::list<int>::iterator it;
    for (it = values->begin(); it != values->end(); it++)
    {
        totalSum += (double)*it;
        count++;
    }
    if (totalSum == 0 || count == 0)
        return 0;
    return (totalSum / (double)count);
}


void StatisticsModel::setAverageJobCompletionTime()
{
    average_job_completion_time = getAverageForList(&jobCompletionTimes);
}
void StatisticsModel::setMTTF()
{
        MTTF = getAverageForList(&interJobFailureTimes);
}

void StatisticsModel::setAverageSuccessfulVMMigrationTime()
{
     average_successful_VM_Migration_time = getAverageForList(&successfulVMMigrationTimes);
}

void StatisticsModel::setAvgTimeSpentInVMMigrationTime()
{
     int average_failed_VM_Migration_time = getAverageForList(&failedVMMigrationTimes);

}

void StatisticsModel::setAverageJobsInInitialSetup()
{
    average_jobs_in_initial_setup = getAverageForList(&jobsInInitialSetup);
}

void StatisticsModel::setAverageJobsInParkingLot()
{
     average_jobs_in_parking_lot = getAverageForList(&jobsInParkingLot);
}

void StatisticsModel::setAverageJobQueueSize()
{
     average_job_queue_size = getAverageForList(&jobQueueSize);
}

void StatisticsModel::setAverageCarsInParkingLot()
{
     average_cars_in_parking_lot = getAverageForList(&carsInParkingLot);
}

void StatisticsModel::setAverageJobStats()
{

     average_timeSpentInProcessing = getAverageForList(&timeSpentInProcessing);
     average_timeSpentInInitialSetup = getAverageForList(&timeSpentInInitialSetup);
     average_timeSpentInBackup = getAverageForList(&timeSpentInBackup);
     average_timeSpentInFinalization = getAverageForList(&timeSpentInFinalization);
     average_timeSpentInVMMigration = getAverageForList(&timeSpentInVMMigration);

}


void StatisticsModel::PrintResults()
{

  //int jobs_completed = jobs_completed;
  int jobs_total = jobs_completed + jobs_failed;

  int vm_migrations_successful = count_success_migrate_vm;
  int vm_migrations_failed = count_failed_migrate_vm;
  int vm_migrations_total = count_success_migrate_vm + count_failed_migrate_vm;

  setAverageJobCompletionTime();
  setMTTF();
  setAverageSuccessfulVMMigrationTime();
  setAverageJobsInInitialSetup();
  setAverageJobsInParkingLot();
  setAverageJobQueueSize();
  setAverageCarsInParkingLot();
  setAverageJobStats();

  *_log.info << "Results" << std::endl;
  *_log.info << "==============================" << std::endl;
  *_log.info << "Total Car Arrivals: " << cars_arrived << std::endl;
  *_log.info << "Total Car Departed: " << cars_departed << std::endl;


  *_log.info << "Completed Jobs: "  << jobs_completed << std::endl;
  *_log.info << "Failed Jobs: " << jobs_failed << std::endl;
  *_log.info << "Total Jobs: " << jobs_total << std::endl;

  *_log.info << "Successful VM Migrations: " << vm_migrations_successful << std::endl;
  *_log.info << "Failed VM Migrations: " <<  vm_migrations_failed << std::endl;
  *_log.info << "Total VM Migrations: " << vm_migrations_total << std::endl;

  *_log.info << "Average Job Completion Time: " << average_job_completion_time << std::endl;
  *_log.info << "MTTF : " << MTTF << std::endl;
  *_log.info << "Average Successful VM Migration Time : " << average_successful_VM_Migration_time << std::endl;
  *_log.info << "Average Jobs In Initial Setup : " << average_jobs_in_initial_setup << std::endl;
  *_log.info << "Average Jobs In Parking Lot  : " << average_jobs_in_parking_lot << std::endl;
  *_log.info << "Average Job Queue Size : " << average_job_queue_size << std::endl;
  *_log.info << "Average Cars In Parking Lot  : " << average_cars_in_parking_lot << std::endl;

  *_log.info << "Average time Spent In Processing     : " << average_timeSpentInProcessing    << std::endl;
  *_log.info << "Average time Spent In InitialSetup   : " << average_timeSpentInInitialSetup  << std::endl;
  *_log.info << "Average time Spent In Backup         : " << average_timeSpentInBackup        << std::endl;
  *_log.info << "Average time Spent In Finalization   : " << average_timeSpentInFinalization  << std::endl;
  *_log.info << "Average time Spent In VMMigration    : " << average_timeSpentInVMMigration   << std::endl;



}

void StatisticsModel::WriteResults()
{

  //int jobs_completed = jobs_completed;
  int jobs_total = jobs_completed + jobs_failed;

  int vm_migrations_successful = count_success_migrate_vm;
  int vm_migrations_failed = count_failed_migrate_vm;
  int vm_migrations_total = count_success_migrate_vm + count_failed_migrate_vm;

  setAverageJobCompletionTime();
  setMTTF();
  setAverageSuccessfulVMMigrationTime();
  setAverageJobsInInitialSetup();
  setAverageJobsInParkingLot();
  setAverageJobQueueSize();
  setAverageCarsInParkingLot();
  setAverageJobStats();

  _results.results <<",Results," << cars_arrived
       << "," << cars_departed
       << "," << jobs_completed
       << "," << jobs_failed
       << "," << jobs_total
       << "," << vm_migrations_successful
       << "," << vm_migrations_failed
       << "," << vm_migrations_total
       << "," << average_job_completion_time
       << "," << MTTF
       << "," << average_successful_VM_Migration_time
       << "," << average_jobs_in_initial_setup
       << "," << average_jobs_in_parking_lot
       << "," << average_job_queue_size
       << "," << average_cars_in_parking_lot
       << "," << average_timeSpentInProcessing
       << "," << average_timeSpentInInitialSetup
       << "," << average_timeSpentInBackup
       << "," << average_timeSpentInFinalization
       << "," << average_timeSpentInVMMigration  << std::endl;


/*
    std::list<int>::iterator it;
    for (it = jobsInParkingLot.begin(); it != jobsInParkingLot.end(); it++)
    {
        _results.results_jobsInParkingLot << *it << std::endl;
    }


    for (it = carsInParkingLot.begin(); it != carsInParkingLot.end(); it++)
    {
        _results.results_carsInParkingLot << *it << std::endl;
    }
*/
}
