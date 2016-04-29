//File:         VehicleParking.cpp
//Project name: To simulate the datacenter for a vehicle parking lot in an Airport.
//Description:  The goal of the project is to simulate a datacenter implemented on the cars in the parking lot of a medium sized airport.
//              As cars arrive and depart randomly, the challenge facing the implementation of the datacenter is to maintain high availability
//              and reliability in the face of the dynamically changing resources. Tradeoffs will be identified and analyzed and several
//              possible solutions will be contrasted. The project is deliberately open ended, allowing each student to add performance-enhancing
//              "bells and whistles".
//Author1:      Aida Ghazizadeh
//Email:        aghaziza@cs.odu.edu
//Author2:      Srinivas Havanur
//Email:        shavanur@cs.odu.edu
//Submitted to: Dr. Stephen Olariu
//Submitted on: 04 December 2015
//Language:     C++

#include "Job.hpp"

Job::Job()
{
  job_flag_start_migration = false;
  job_flag_end_migration = false;
  data_replication_time_to_same_cluster=0;
  data_replication_time_to_same_region=0;
  data1_car_number = -1;
  data2_car_number = -1;
  
  assigned = false;													
  jobProcessingComplete = false; 
  jobComplete = false;
  
  jobSize = 0;
  jobSizeLeftToProcess = 999;

  
}

//This displays the job information which is assigned to all the cars in the parking lot as soon as simulation starts.
void Job::display_job_information(std::ofstream& outFile)
{
  outFile<<"\n";
  outFile<<"-----------------------------------------"<<"\n";
  outFile<<"		Job Details		        "<<"\n";
  outFile<<"-----------------------------------------"<<"\n";
  outFile<<"job number : "<<job_number<<"\n";
  outFile<<"job size : "<<VM_size<<"\n";
  outFile<<"car number that this job is assigned to : "<<car_number<<"\n";
}


/*
void Job::calculate_VM_size(){
  // our jobs are between 1 GB and 5 GB
  VM_size= rand()%(5000-1000)+1000;                           
  VM_migration_remained = VM_size;
}


// Calculates the time it takes to complete a job in a car.
void Job::calculate_job_duration(){                                          
  //we assume that 1 MB takes 1/10 minute to finish 
  job_duration= (VM_size*0.1);												 
  job_duration_remained = job_duration;
}																
*/
