//File:         Car.hpp
//Description:

#ifndef __CAR_HPP__
#define __CAR_HPP__

#include <fstream>
#include <list>
#include "Job.hpp"
#include "MigrationJob.hpp"
#include "JobTask.hpp"

class Job;
class MigrationJob;
class JobTask;

// This includes information about all the cars including which spot the car is currently parked, along with arrival and departure time.
class Car
{
  public:
    int car_spot_number;
    signed short int car_cluster_number;
    signed short int car_group_number, car_region_number;
    int arrival_time_of_car;
    int departure_time_of_car;
    int job_number;
	Job * job;

    //A list of DataMigationTask coming IN to the car.
    std::list<MigrationJob*> ActiveDataMigrationTasks;

    //A list of Job Tasks that are completed
    std::list<JobTask*> CompletedDataMigrationTasks;

    Car();

	bool canAcceptJob();
	void printCarDetails(bool printChildDetails, std::string tab);
};

#endif
