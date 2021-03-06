//File:         Car.cpp
//Description:

#include "Car.hpp"


Car::Car()
{

  car_spot_number=-1;
  car_cluster_number= -1;
  car_group_number = -1;
  car_region_number = -1;
  job_number = 0;
  arrival_time_of_car = -1;
  departure_time_of_car = -1;
  job = NULL;
}




//Car has no current job, and isn't being migrated to
bool Car::canAcceptJob()
{
  if (job == NULL)
    return true;
  return false;
}



void Car::printCarDetails(bool printChildDetails, std::string tab)
{
    Logger log;

    *log.debug << tab <<  "Car at space:" << car_spot_number << std::endl;
    *log.debug << tab <<  "    Arrived at   " << arrival_time_of_car << std::endl;
    *log.debug << tab <<  "    Departing at " << departure_time_of_car << std::endl;

	 if (job != NULL)
	 {
	     if (printChildDetails)
	         job->printJobDetails(true, tab + "    ");
	 }

	 if (!ActiveDataMigrationTasks.empty())
     {
        std::list<MigrationJob*>::iterator it;
        for(it = ActiveDataMigrationTasks.begin(); it != ActiveDataMigrationTasks.end(); it++)
        {
            (*it)->printMigrationJobDetails(true, tab + "    ");
        }
     }
}
