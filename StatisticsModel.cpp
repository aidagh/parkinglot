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



std::list<int> StatisticsModel::jobCompletionTimes;
std::list<int> StatisticsModel::interJobFailureTimes;
std::list<int> StatisticsModel::successfulVMMigrationTimes;

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

void StatisticsModel::LogFailedVMMigration()
{
	count_failed_migrate_vm++;
}


void StatisticsModel::LogJobCompletionTime(int completionTime)
{
  jobCompletionTimes.push_back(completionTime);

}


void StatisticsModel::setAverageJobCompletionTime()
{
    int totalSum = 0;
    int count = 0;

    std::list<int>::iterator it;
    for (it = jobCompletionTimes.begin(); it != jobCompletionTimes.end(); it++)
    {
        totalSum += *it;
        count++;
    }
    if (totalSum == 0 || count == 0)
        return;
    average_job_completion_time = totalSum / count;
}
void StatisticsModel::setMTTF()
{
    int totalSum = 0;
    int count = 0;

    std::list<int>::iterator it;
    for (it = interJobFailureTimes.begin(); it != interJobFailureTimes.end(); it++)
    {
        totalSum += *it;
        count++;
    }
    if (totalSum == 0 || count == 0)
        return;
    MTTF = totalSum / count;
}

void StatisticsModel::setAverageSuccessfulVMMigrationTime()
{
    int totalSum = 0;
    int count = 0;

    std::list<int>::iterator it;
    for (it = successfulVMMigrationTimes.begin(); it != successfulVMMigrationTimes.end(); it++)
    {
        totalSum += *it;
        count++;
    }
    if (totalSum == 0 || count == 0)
        return;
    average_successful_VM_Migration_time = totalSum / count;
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
       << "," << average_successful_VM_Migration_time << std::endl;



}
