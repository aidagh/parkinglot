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



//
//// Displays all car information including the spot number to which the car belongs to. Initially when the simulation starts
//// all the parking spots will be occupied by cars.
//void Car::display_car_information(std::ofstream& outFile)                  
//{                                                                
//  outFile<<"\n";
//  outFile<<"-----------------------------------------"<<"\n";
//  outFile<<"		Car Details		        "<<"\n";
//  outFile<<"-----------------------------------------"<<"\n";
//  outFile<<"car number : "<<car_number<<"\n";
//  outFile<<"car spot number : "<<car_spot_number<<"\n";
//  outFile<<"job number assigned to this car : "<<job_number<<"\n";
//  outFile<<"departure time of this car : "<<departure_time_of_car<<"\n";
//  outFile<<"arrival time of this car : "<<arrival_time_of_car<<"\n";
//  outFile<<"The Residency time: "<<residency_time<<"\n";
//  outFile<<"Car Turned away: "<<turned_away<<"\n";
//}
//
//
////Calculates the departure time of a car when simulation starts. This is between 1-2560 cars
//// min residency time of a car is 24 hours (1440 minutes) and max residency time is 7 days (10080 minutes)
//// this function is for cars that are already in the parking lot when we start our simulation
//void Car::calculate_departure_time()
//{                                
//  departure_time_of_car= rand()%(10080-1440)+1440;                          
//}																     
//
//
//// Car arrives 60 minutes earlier to the flight departure hence the arrival time.
//void Car::get_arrival_time_of_car(std::ifstream& inFile)
//{
//  inFile>>departure_time_of_flight;
//  arrival_time_of_car = departure_time_of_flight - 60;
//}
//
//// Get the departure time of car between 2561 to 5000 cars by making use of arrival time of a flight.														
////The departure time is 60 minutes after the arrival.
//void Car::get_departure_time_of_car(std::ifstream& inFile)
//{	
//  inFile>>arrival_time_of_flight;
//  departure_time_of_car = arrival_time_of_flight + 60;
//}
//
////Calculates the residency time of a car based on the arrival and departure time of a car.
//void Car::calculate_residency_time_of_car()                          
//{
//  residency_time = departure_time_of_car - arrival_time_of_car;
//}
//
//
////This displays the details of a car which may fail if we don't do the migration.
//void Car::display_failed_job_car_details(std::ofstream& outFileFailed)    
//{
//  outFileFailed<<"\n";
//  outFileFailed<<"-----------------------------------------"<<"\n";
//  outFileFailed<<"		Failed Job Car Details		        "<<"\n";
//  outFileFailed<<"-----------------------------------------"<<"\n";
//  outFileFailed<<"car number : "<<car_number<<"\n";
//  //outFileFailed<<"car spot number : "<<car_spot_number<<"\n";
//  outFileFailed<<"job number assigned to this car : "<<job_number<<"\n";
//  outFileFailed<<"departure time of this car : "<<departure_time_of_car<<"\n";
//  outFileFailed<<"arrival time of this car : "<<arrival_time_of_car<<"\n";
//}
//
//
////This displays the details of a car which may pass during the simulation.
//void Car::display_pass_job_car_details(std::ofstream& outFilePassJob)    
//{
//  outFilePassJob<<"\n";
//  outFilePassJob<<"-----------------------------------------"<<"\n";
//  outFilePassJob<<"		Pass Job Car Details		        "<<"\n";
//  outFilePassJob<<"-----------------------------------------"<<"\n";
//  outFilePassJob<<"car number : "<<car_number<<"\n";
//  //outFilePassJob<<"car spot number : "<<car_spot_number<<"\n";
//  outFilePassJob<<"job number assigned to this car : "<<job_number<<"\n";
//  outFilePassJob<<"departure time of this car : "<<departure_time_of_car<<"\n";
//  outFilePassJob<<"arrival time of this car : "<<arrival_time_of_car<<"\n";
//}
//