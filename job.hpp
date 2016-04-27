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



// This class stores information about the jobs.
class job
{
  public:
    //car number that the job belongs to
	int car_number;
    int job_number;
    double VM_size;
    double VM_migration_remained;
    bool completed;
    //meaning this job was assigned or not assigned to a car
	bool assigned;													
	
    double job_duration;  // in minute
    double data_this_job_will_produce;
    double data_storage_time;
    double job_duration_remained;
    int data1_car_number;
    std::string replicated_data;
    int data2_car_number;
    int data3_car_number;
    int data_replication_time_to_same_cluster;
    int data_replication_time_to_same_region;
    int migrated_successfully; // 2 for success and 3 for fail
    bool job_flag_start_migration;
    bool job_flag_end_migration;
    int car_num_migration_to;

    job();
    void display_job_information(std::ofstream& outFile);
    void calculate_VM_size();
    void calculate_job_duration();
    
};

