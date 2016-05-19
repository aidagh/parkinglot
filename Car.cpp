//File:         Car.cpp
//Description:

#include "Car.hpp"


Car::Car()
{

  // This is to keep track how many cars turned away when they try to occupy the parking space. Initially set to -1.
  // turned_away=0 - Car didn't turn away or got parking space.
  // turned_away=1 - Car turned away
//  turned_away=-1;

  car_spot_number=-1;
//  job_has_been_migrated=false;
//  car_flag_start_migration=false;
//  car_flag_end_migration=false;
//  car_num_migration_to = -1;
 // print_migration_flag_counter=0;

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
