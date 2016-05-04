//File:         StatisticsModel.hpp
//Description:  


#include "StatisticsModel.hpp"


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