//File:         StatisticsModel.hpp
//Description:


#include "StatisticsModel.hpp"
#include <list>
int StatisticsModel::cars_arrived = 0;
int StatisticsModel::cars_departed = 0;
int StatisticsModel::jobs_completed = 0;
int StatisticsModel::jobs_failed = 0;
int StatisticsModel::count_failed_migrate_vm = 0;
int StatisticsModel::count_success_migrate_vm = 0;

std::list<int> StatisticsModel::jobCompletionTimes;

void StatisticsModel::Initialize()
{
  jobs_completed = 0;
  count_failed_migrate_vm = 0;
  count_success_migrate_vm = 0;

  jobCompletionTimes = std::list<int>();

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
void StatisticsModel::LogJobFailed()
{
	jobs_failed++;
}

void StatisticsModel::LogSuccessfulVMMigration()
{
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


void StatisticsModel::PrintResults()
{

  //int jobs_completed = jobs_completed;
  int jobs_total = jobs_completed + jobs_failed;

  int vm_migrations_successful = count_success_migrate_vm;
  int vm_migrations_failed = count_failed_migrate_vm;
  int vm_migrations_total = count_success_migrate_vm + count_failed_migrate_vm;




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


}
