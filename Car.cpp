//File:         Car.cpp
//Description:

#include "Car.hpp"


Car::Car()
{

  car_spot_number=-1;
  job_number = 0;
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

	 if (!DataMigrationTasks.empty())
     {
        std::list<MigrationJob*>::iterator it;
        for(it = DataMigrationTasks.begin(); it != DataMigrationTasks.end(); it++)
        {
            (*it)->printMigrationJobDetails(true, tab + "    ");
        }
     }
}
