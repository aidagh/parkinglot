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



// This includes information about all the cars including which spot the car is currently parked, along with arrival and departure time.
class car
{
  public: 
    int car_number;
    int car_spot_number;
    int arrival_time_of_car;
    int departure_time_of_flight;
    int arrival_time_of_flight;
    int departure_time;
    int job_number;
    int residency_time;
    int turned_away;
    
	// to check if this car has a job (VM) or doesn't have a job (VM)
	bool busy;                                                       
    
	// to check if we migrated the job on this car to another car yet yet	
	bool job_has_been_migrated;									  
	
    bool car_flag_start_migration;
    int print_migration_flag_counter;
    bool car_flag_end_migration;
    int car_num_migration_to;
		
    car();
    
    void display_car_information(std::ofstream& outFile);
    void calculate_departure_time();
    void get_arrival_time_of_car(std::ifstream& inFile);
    void get_departure_time_of_car(std::ifstream& inFile);
    void calculate_residency_time_of_car();
    void display_failed_job_car_details(std::ofstream& outFileFailed);
    void display_pass_job_car_details(std::ofstream& outFilePassJob);
  
};

