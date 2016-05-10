//File:         StatisticsModel.hpp
//Description:


#include "StatisticsModel.hpp"

int StatisticsModel::jobs_completed = 0;
int StatisticsModel::count_migrated_successfully = 0;
int StatisticsModel::count_failed_to_migrate = 0;

void StatisticsModel::LogJobCompleted()
{
	jobs_completed++;
}

void StatisticsModel::LogSuccessfulMigration()
{
	count_migrated_successfully++;
}

void StatisticsModel::LogFailedMigration()
{
	count_failed_to_migrate++;
}
