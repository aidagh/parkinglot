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

/*
List of Updates:
Split into header and class files (car, job, spot_location, time)
Rename cars to car, jobs to job, 

*/

/*
TO DO:
1. Add Configuration class
2. Add Statistics class
3. Fix bandwidth
4. Organize loops
5. Drop input files
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <map>
#include <list>
#include <queue>


#include "TimeModel.hpp"
#include "Random.hpp"
#include "Configuration.hpp"
#include "Configuration.cpp"
#include "Car.hpp"
#include "Car.cpp"
#include "Job.hpp"
#include "Job.cpp"
#include "CarResidencyDistributionModel.hpp"
#include "CarResidencyDistributionModel.cpp"
#include "StatisticsModel.hpp"
#include "StatisticsModel.cpp"
#include "CarModel.hpp"
#include "CarModel.cpp"
#include "JobModel.hpp"
#include "JobModel.cpp"
//#include "spot_location.hpp"
//#include "spot_location.cpp"



using namespace std;

void RegionCenter1();
void RegionCenter2();
void RegionCenter3();
void RegionCenter4();


Configuration _configuration;
int jobs_completed =0;
int count_migrated_successfully = 0;
int count_failed_to_migrate = 0;
int Array_first_spot_of_cluster[65];
int turned_away_count =0;

int cluster_count_migrating[65];
int cluster_bandwidth[65];
int minimum_migration_bandwidth;
int START_TIME_MIGRATION = 60;
const int END_TIME = 10080;                                                    // The total time for which our simulation runs in minutes. In other words, the simulation will run for
int spot_var;

//const double HD_bandwidth = 12000;                                            // The disk bandwidth 200MB/s is expressed in minutes. This disk bandwidth is considered from hennessy-patterson text book.
//                                                                              //Disk bandwidth is useful to calculate the time it takes to store the data to the local disk of car.
int jobfailCounter=0, jobPassCounter=0;
const int BUFFER_TIME_FOR_DATA_REPLICATION = 40;							  // the minimum buffer time that we picked that is needed for data replication(in minutes); we pick this number because we calculated that the replication time to same cluster is 17 mins and to a different cluster is 35 mins

/*
class spot_location                                                          //This class includes all information about the parking spots and also it keeps track of whether parking spot is occupied or not.
{

  public: int spot_number;
    int cluster_number;
    int region_number;
    int group_center_number;
    int occupied;
    int occupied_by_car_number;
    
  public: void spot_locations(int sno, int cno, int rno, int gcnumber, int occup)
  {
    spot_number = sno;
    cluster_number = cno;
    region_number = rno;
    group_center_number = gcnumber;
    occupied = occup;
  }
  
  void display_spot_information(ofstream& outFile)                    // This displays all information about the parking spots.
  {
    outFile<<"\n";
    outFile<<"-----------------------------------------"<<"\n";
    outFile<<"		Spot Details		        "<<"\n";
    outFile<<"-----------------------------------------"<<"\n";
    outFile<<"Spot number : "<<spot_number<<"\n";
    outFile<<"Cluster number : "<<cluster_number<<"\n";
    outFile<<"Region number : "<<region_number<<"\n";
    outFile<<"Group Center number : "<<group_center_number<<"\n";
    outFile<<"Occupied : "<<occupied<<"\n";
  }
  
};

class cars                                                                // This includes information about all the cars including which spot the car is currently parked, along with arrival and departure time.
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
    bool busy;                                                       // to check if this car has a job (VM) or doesn't have a job (VM)
    bool job_has_been_migrated;									  // to check if we migrated the job on this car to another car yet yet	
    bool car_flag_start_migration;
    int print_migration_flag_counter;
    bool car_flag_end_migration;
    int car_num_migration_to;
		
		 cars()
		 {
		     turned_away=-1;                                             // This is to keep track how many cars turned away when they try to occupy the parking space. Initially set to -1.
                                                                         // turned_away=0 - Car didn't turn away or got parking space.
                                                                         // turned_away=1 - Car turned away
			car_spot_number=-1;
             job_has_been_migrated=false;
			 car_flag_start_migration=false;
	         car_flag_end_migration=false;
			 car_num_migration_to = -1;
			 print_migration_flag_counter=0;
         }

        void display_car_information(ofstream& outFile)                  // Displays all car information including the spot number to which the car belongs to. Initially when the simulation starts
		{                                                                // all the parking spots will be occupied by cars.
			outFile<<"\n";
			outFile<<"-----------------------------------------"<<"\n";
			outFile<<"		Car Details		        "<<"\n";
			outFile<<"-----------------------------------------"<<"\n";
			outFile<<"car number : "<<car_number<<"\n";
			outFile<<"car spot number : "<<car_spot_number<<"\n";
			outFile<<"job number assigned to this car : "<<job_number<<"\n";
			outFile<<"departure time of this car : "<<departure_time<<"\n";
            outFile<<"arrival time of this car : "<<arrival_time_of_car<<"\n";
            outFile<<"The Residency time: "<<residency_time<<"\n";
            outFile<<"Car Turned away: "<<turned_away<<"\n";


		}





		
        void calculate_departure_time(){                                //Calculates the departure time of a car when simulation starts. This is between 1-2560 cars

            departure_time= rand()%(10080-1440)+1440;                              // min residency time of a car is 24 hours (1440 minutes) and max residency time is 7 days (10080 minutes)
        }																// this function is for cars that are already in the parking lot when we start our simulation

        void get_arrival_time_of_car(ifstream& inFile){                 // Car arrives 60 minutes earlier to the flight departure hence the arrival time.

            inFile>>departure_time_of_flight;
            arrival_time_of_car = departure_time_of_flight - 60;
        }
                                                                        
                                                                        
        void get_departure_time_of_car(ifstream& inFile){				// Get the departure time of car between 2561 to 5000 cars by making use of arrival time of a flight.
																		//The departure time is 60 minutes after the arrival.
            inFile>>arrival_time_of_flight;
            departure_time = arrival_time_of_flight + 60;
        }

        void calculate_residency_time_of_car()                          //Calculates the residency time of a car based on the arrival and departure time of a car.
        {
            residency_time = departure_time - arrival_time_of_car;
        }

        void display_failed_job_car_details(ofstream& outFileFailed)    //This displays the details of a car which may fail if we don't do the migration.
        {
            outFileFailed<<"\n";
			outFileFailed<<"-----------------------------------------"<<"\n";
			outFileFailed<<"		Failed Job Car Details		        "<<"\n";
			outFileFailed<<"-----------------------------------------"<<"\n";
			outFileFailed<<"car number : "<<car_number<<"\n";
			//outFileFailed<<"car spot number : "<<car_spot_number<<"\n";
			outFileFailed<<"job number assigned to this car : "<<job_number<<"\n";
			outFileFailed<<"departure time of this car : "<<departure_time<<"\n";
            outFileFailed<<"arrival time of this car : "<<arrival_time_of_car<<"\n";

        }

		void display_pass_job_car_details(ofstream& outFilePassJob)    //This displays the details of a car which may pass during the simulation.
        {
            outFilePassJob<<"\n";
			outFilePassJob<<"-----------------------------------------"<<"\n";
			outFilePassJob<<"		Pass Job Car Details		        "<<"\n";
			outFilePassJob<<"-----------------------------------------"<<"\n";
			outFilePassJob<<"car number : "<<car_number<<"\n";
			//outFilePassJob<<"car spot number : "<<car_spot_number<<"\n";
			outFilePassJob<<"job number assigned to this car : "<<job_number<<"\n";
			outFilePassJob<<"departure time of this car : "<<departure_time<<"\n";
            outFilePassJob<<"arrival time of this car : "<<arrival_time_of_car<<"\n";

        }






};

class jobs                                                            // This class stores information about the jobs.
{
  public:
    int car_number;                                                 //car number that the job belongs to
    int job_number;
    double VM_size;
    double VM_migration_remained;
    bool completed;
    bool assigned;													//meaning this job was assigned or not assigned to a car
    double job_duration;                                            // in minute
    double data_this_job_will_produce;
    double data_storage_time;
    double job_duration_remained;
    int data1_car_number;
    string replicated_data;
    int data2_car_number;
    int data3_car_number;
    int data_replication_time_to_same_cluster;
    int data_replication_time_to_same_region;
    int migrated_successfully; // 2 for success and 3 for fail
    bool job_flag_start_migration;
    bool job_flag_end_migration;
    int car_num_migration_to;

    jobs()
    {
      job_flag_start_migration = false;
      job_flag_end_migration = false;
      data_replication_time_to_same_cluster=0;
      data_replication_time_to_same_region=0;
      data1_car_number = -1;
      data2_car_number = -1;
    }


    void display_job_information(ofstream& outFile)                 //This displays the job information which is assigned to all the cars in the parking lot as soon as simulation starts.
    {
			outFile<<"\n";
			outFile<<"-----------------------------------------"<<"\n";
			outFile<<"		Job Details		        "<<"\n";
			outFile<<"-----------------------------------------"<<"\n";
			outFile<<"job number : "<<job_number<<"\n";
            outFile<<"job size : "<<VM_size<<"\n";
            outFile<<"car number that this job is assigned to : "<<car_number<<"\n";
            

    }



    void calculate_VM_size(){
        VM_size= rand()%(5000-1000)+1000;                           // our jobs are between 1 GB and 5 GB
		VM_migration_remained = VM_size;
    }

	void calculate_job_duration(){                                                    // Calculates the time it takes to complete a job in a car.
        job_duration= (VM_size*0.1);												 //we assume that 1 MB takes 1/10 minute to finish 
        job_duration_remained = job_duration;
    }																

};


class Time
{
    public:
    int minute;

    Time(){
        minute = 0;
    }

    void increment(){
        minute++;
    }

};

*/

Car cars_list[5001];

//spot_location spot_loc[2561];

Job jobs_list[5001];

void generate_array(){

    for(int i=0; i <=64; i++){

        Array_first_spot_of_cluster[i]=0;
    }

    Array_first_spot_of_cluster[1]=1;

    for(int i=2; i <=64; i++){

        Array_first_spot_of_cluster[i]=Array_first_spot_of_cluster[i-1] + 40;
    }


}


                                                                        /*This function is to find the carnumber within the same cluster which has a longest job duration.
                                                                          This will be useful to replicate the job to the car belonging to same cluster. (used for data replication) 
																		  In case we use the max method which is choosing a car with the max residency time.	
																		*/
/*int max_departure (int spotnumber,int spot_number_of_this_job)
{
    int spot_num=spotnumber;
    for(int i=spotnumber+1;i<=spotnumber+39;i++)
    {
        if(i == spot_number_of_this_job)                                //This will skip the assigning the job to same car in the cluster.
        {

             continue;
        }

        if(cars_list[spot_num].departure_time <cars_list[i].departure_time)
        spot_num = i;

    }
    return cars_list[spot_num].car_number;
}
	*/														//This is used to calculate congestion bandwidth by considering count of cars which is migrating at time t (Count of cars are calculated in calculate_congestion() function) 
void calculate_bandwidth()
{

	for(int l=1;l<=64;l++)
	{
		cluster_bandwidth[l]=0;		//initialize our array
	}
	
	for(int b=1;b<=64;b++)
	{
		if(cluster_count_migrating[b] == 0)
		{
		cluster_bandwidth[b] = _configuration.BandwidthPerSecondForCluster;
		}
		else
		{
			cluster_bandwidth[b] = _configuration.BandwidthPerSecondForCluster / cluster_count_migrating[b];
		}
	}
}

void calculate_congestion(int time)       		//this function updates the cluster_count_migrating array which keeps track of the number of cars that are migrating at time t in every cluster. we need this to calculate congestion in eaach cluster later in our code.        
{
	int k,j,cnumber;
	//ofstream calculate_cong;
//	calculate_cong.open("test123.txt", std::fstream::app);
	for(int l=1;l<=64;l++)
	{
		cluster_count_migrating[l]=0;		//initialize our array
	}
	
	for (int c=1; c<=5000; c++)					//loops through all the cars 
	{
			
		int job_num_var = cars_list[c].job_number;

		if ( cars_list[c].job_has_been_migrated==false && time+START_TIME_MIGRATION >= cars_list[c].departure_time_of_car && cars_list[c].departure_time_of_car>=time && cars_list[c].car_spot_number != -1)   // if the car is migrating				
	//	if(cars_list[c].car_flag_start_migration == true && cars_list[c].car_spot_number != -1)

		{	
				
			// we want to find out the cluster number of this car
			k=1;j=40;cnumber=1;		// k & j are for our loop control variables. each cluster consists of 40 cars. this loop start from cluster 1 (k=1). cnumber is the cluster number
			while(1)				//infinite loop
			{
				if(cnumber>64)		// we don't have cluster number more than 64, so when it is 64, it will break the loop
					break;
					
				if(cars_list[c].car_spot_number>=k && cars_list[c].car_spot_number<=j)	//find the cluster number of this car. for example if spot num is 1-40 cluster number will be 1
				{
					
				//	calculate_cong << "Time: "<< time << "	Car number: "<<cars_list[c].car_spot_number<<" and Cluster number: "<<cnumber<<endl;
					cluster_count_migrating[cnumber]++;
					break;							//while we find the cluster number break the loop
				}
				k=k+40; 	// our control variables
				j=k+39;
				cnumber++;
			}
			
			
		}
			
		
	}
}






int randomly_picked_car_datareplication_same_cluster (int spotnumber,int spot_number_of_this_job, int car_number_of_this_job)     //This function randomly picks a car for data replication which has a sufficient buffer time.
{

    int spot_num, arr[41];											  //declare an array called arr 
	int flag =0;													 // helps us to know if all the elements in the array are -1 or not 	
	int index=1;
	

		
	for(int k=0; k<41; k++){
	
		arr[k]=-1;							                           // assigns -1 to all of the elements of the array and when we find the car that we want it will change the index
	}

    for(int i=spotnumber;i<=spotnumber+39;i++)                         // this for loop goes through cars in the same cluster
    {

        if(i == spot_number_of_this_job)                                //This will skip the assigning the job to same car in the cluster.
        {
             continue;
        }

        if(cars_list[car_number_of_this_job].departure_time_of_car + BUFFER_TIME_FOR_DATA_REPLICATION <cars_list[i].departure_time_of_car )         //finds the car with a departure time of BUFFER_TIME_FOR_DATA_REPLICATION time more than the departure time of the car 
			arr[index]=i;
                                                                                                                        //when it  finds the car, it will save the spot number of the car in the array

		index++;

    }
	for(int j=1;j<=40;j++)							
	{
		if(arr[j]>0)
		{
			flag=1;			//if we find an element that is not -1 then the flag is 1 
			break;
		}
		else
			flag=0;
	}
	if(flag == 1)
	{
			do
			{
				spot_num = arr[rand() % (sizeof(arr) / sizeof(arr[0]))];          // This is to fetch the random car number from an array. (it randomly picks an item from the array) 

			}while(spot_num == -1);
	}

	else return -1000;

    return cars_list[spot_num].car_number;
}



/* 
int max_residency_not_busy_car(int time){                       //This will find a car with the maximum residency time that doesn't have a job assigned to it.
	ofstream outTestOutput;
	outTestOutput.open("test.txt");													// we don't use it is case we are not calculating the max residency time 
    int car_num = -1;
    int residency_time_temp= -1;
    for ( int i=1; i<=5000; i++){
			//	outTestOutput<<"Car busy: "<<cars_list[i].busy<<" Car departure time: "<<cars_list[i].departure_time<<" Car spot number: "<<cars_list[i].car_spot_number<<" Car residency time: "<<cars_list[i].residency_time<<endl;
        if(cars_list[i].busy == false && cars_list[i].departure_time > time && cars_list[i].car_spot_number != -1 && cars_list[i].residency_time > residency_time_temp  ){
				
            residency_time_temp= cars_list[i].residency_time;
            car_num = cars_list[i].car_number;
        }

    }
    return car_num;

}
 */
 
 
 int max_residency_not_busy_car(int time){                       //This will find a car with the maximum dept time that doesn't have a job assigned to it.
	ofstream outTestOutput;
	outTestOutput.open("test.txt");													// we don't use it is case we are not calculating the max dept time 
    int car_num = -1;
    int dept_time_temp= -1;
    for ( int i=1; i<=5000; i++){
			//	outTestOutput<<"Car busy: "<<cars_list[i].busy<<" Car departure time: "<<cars_list[i].departure_time<<" Car spot number: "<<cars_list[i].car_spot_number<<" Car residency time: "<<cars_list[i].residency_time<<endl;
        if(cars_list[i].busy == false && cars_list[i].departure_time_of_car > time && cars_list[i].car_spot_number != -1 && cars_list[i].departure_time_of_car > dept_time_temp  ){
				
            dept_time_temp= cars_list[i].departure_time_of_car;
            car_num = cars_list[i].car_number;
        }

    }
    return car_num;

}

/*
                                                            // This is to replicate the data to other cluster.
                                                            //This function gets the spot location of other cluster to which data should be replicated(same GC and same Region).
int generate_random_cluster_number_in_a_region(int GC_number_of_this_car, int spot_number_of_this_job, int cluster_number_of_this_car, int car_number_of_this_job){

	int car_number;
	int spot_number;
	int random_number;
	int random_cluster_number=0;
	int GC_num;

	generate_array();

	random_number=1;
	for(GC_num=1;GC_num<=16;GC_num++)
	{
		if (GC_number_of_this_car==GC_num){

			//int random_cluster_number=cluster_number_of_this_car;
			random_cluster_number=0;
			do
			{
				random_cluster_number= rand()%4 + random_number ; //generate 1 to 4
			}while(random_cluster_number==cluster_number_of_this_car);

			//car_number = max_departure(Array_first_spot_of_cluster[random_cluster_number],spot_number_of_this_job);
			car_number= randomly_picked_car_datareplication_same_cluster(Array_first_spot_of_cluster[random_cluster_number],spot_number_of_this_job,car_number_of_this_job);

		}
	   random_number=random_number + 4;

	}


	return car_number;
}
*/

int getClusterNumber(int spotnum)
{
	int clusternum,j;
	int k=1;
	int i=1;
	while(i<=2521){
	j=i+39;
	
	if(spotnum<=j && spotnum>=i){
		clusternum=k;
		break;		
	}
	else k++;
	i=i+40;

	}
return clusternum;	
	
}


CarModel _carModel;
TimeModel _timeModel;


int main()
{
	_carModel.Initialize();
	_timeModel.initialize();
	
	int a;
	std::cin >> a;
	
	while (_timeModel.getTime() < _configuration.MaxTime)
	{
	  std::cout << "Time: " << _timeModel.getTime() << std::endl;
      _carModel.HandleLeavingVehicles();
	  _carModel.HandleIncomingVehicles();
		
	  _timeModel.increment();
	}
	
}

int oldmain()
{
    int car_participation_count=0, total_cars_count=0;
	//srand(time(0));
//These are handled on the fly now.
//	RegionCenter1();                                        //This will initialize the spot locations of all clusters belonging to region center1.
//	RegionCenter2();                                        //This will initialize the spot locations of all clusters belonging to region center2.
//	RegionCenter3();                                        //This will initialize the spot locations of all clusters belonging to region center3.
//	RegionCenter4();                                        //This will initialize the spot locations of all clusters belonging to region center4.
    ofstream outFile,outFileFailed,outFilePassJob,outFileCarParticipation,outFileTotalCarsArrived, outFileParkingLot, FailedMigratedJobs, outTurnedAway, outFailedReplication, outCongCount, outMigration3,outEndMigration, outJobFailed;
    ifstream inFile,inFile2;
    ofstream outTest, outTest2, outMigration,outMigration2;
	outMigration.open("jobs_started_migration.txt");
	outMigration2.open("jobs_failed.txt");
	outMigration3.open("jobs_csv.txt");
    inFile.open("input_departure_time_of_flight.txt");
    inFile2.open("input_arrival_time_of_flight.txt");
    outTurnedAway.open("TurnedAwayCars.txt");
	outCongCount.open("Congestioncount.txt");
	outJobFailed.open("JobMigrationFailed.txt");
	outEndMigration.open("job_end_migration.txt");
    outFile.open("CarsAndJobDetails.txt");
    outFileFailed.open("PossibleFailedJob.txt");
	outFilePassJob.open("PossiblePassedJob.txt");
    outFileCarParticipation.open("cars_participation_simulation.txt");
    outFileTotalCarsArrived.open("total_cars_for_the_simulation.txt");
    //outTest.open("replicationData.txt");
	//outFailedReplication.open("FailedreplicationData.txt");
    outTest2.open("SuccessfullyMigratedJobs.txt");
    FailedMigratedJobs.open("FailedMigratedJobs.txt");
    ofstream outSpot;
    outSpot.open("SpotDetails.txt");
    outFileParkingLot.open("NewCarsAssignedtoSpot.txt");


                                                            // Assigning the carnumbers for all available 5000 cars
//    for(int i=1; i<=5000; i++)
//	{
//		cars_list[i].car_number = i;
//        cars_list[i].busy = false;
//	}

_carModel.Initialize();
    //Initialize all spot numbers, job numbers, departure time to all the cars
//    for(int i=1; i<=2560; i++)
//	  {
//		cars_list[i].car_spot_number = spot_loc[i].spot_number;
//		spot_loc[i].occupied_by_car_number = i ;
//      cars_list[i].job_number=i;
//      cars_list[i].calculate_departure_time();
//		cars_list[i].calculate_residency_time_of_car();
//		cars_list[i].turned_away=0;
//      cars_list[i].busy = true;
//
//	}



//RF - New cars will be generated on the fly.  see carModel
//      // Initialize -1 for cars outside the range of parking lot.
//   	for(int i=2561; i<=5000; i++)
//   	{
//   		cars_list[i].car_spot_number = -1;
//   
//   	}
  
//RF - New jobs will be generated on the fly.  See jobModel
//   // Initialize all 5000 jobs for job class
//	  for(int i=1; i<=5000; i++)
//		{
//			jobs_list[i].job_number = i;
//			jobs_list[i].calculate_VM_size();
//			jobs_list[i].calculate_job_duration();		//Added by Me						
// 	     jobs_list[i].completed=false;
// 	     jobs_list[i].assigned=false;
//
//		}

//RF - jobs will be assigned to cars on the fly. 
//     The initial state of the parking lot will be handled in the initialize of the carModel and jobModel
//     *****TODO
//	// Assigning jobs to cars and setting the assigned flag for job class.
//    for(int i=1; i<=2560; i++)
//		{
//	
// 	       if(cars_list[i].job_number==jobs_list[i].job_number){
//	            jobs_list[i].car_number=cars_list[i].car_number;
// 	           jobs_list[i].assigned=true;
//	        }
//	        else
//	        {
//	            jobs_list[i].car_number=-1;
//	            jobs_list[i].assigned=false;
//	        }
//		}

    // Getting the arrival time of car from the arrival list of flights from an input file.
    for(int i=2561; i<=5000; i++){

      cars_list[i].get_arrival_time_of_car(inFile);
      cars_list[i].get_departure_time_of_car(inFile2);
      cars_list[i].calculate_residency_time_of_car();
    }


/*
    if(spot_loc[1].cluster_number>64)					// issue we had with this particular car number
    {
        spot_loc[1].spot_number=1;
        spot_loc[1].region_number=1;
        spot_loc[1].cluster_number=1;
        spot_loc[1].group_center_number=1;
        spot_loc[1].occupied=1;
    }
*/

                                                            // Displaying all car and job information
    for(int i=1; i<=5000; i++)
	{

		cars_list[i].display_car_information(outFile);
		int job_number = jobs_list[i].job_number;
		jobs_list[job_number].display_job_information(outFile);		

	}
                                                            //Displays all spot information.
//	for(int i=1;i<=2560;i++)
//	{
//		spot_loc[i].display_spot_information(outSpot);
//	}


                                                            // Simulation time in minutes that is run for 24 hours which is equal to 1440 minutes.
   // Time time;
    //cout << "\nTime is: " <<time.minute;
    for (int i=1; i<=END_TIME; i++){  //1440
        //time.increment();
        cout << "\nTime is: " <<i;
        // If simulation time in minutes exceeds the departure time of car then it means that car
        //has already left and need to initialize the spot location as -1 and job assigned should be set to false.
        
//		Car Loop
//		  1. handle leaving cars
//		  2. decrement job duration 
//		  3. handle incoming cars
//		  4. handle VM Migration
		  
		  
		for(int c=1; c<=5000; c++)
        {
                if(i>=cars_list[c].departure_time_of_car)
                {
 //                   spot_var = cars_list[c].car_spot_number;
 //                   spot_loc[spot_var].occupied_by_car_number = cars_list[c].car_number;
 //                   spot_loc[spot_var].occupied= -1;
 //                   int job_var = cars_list[c].job_number;
 //                   jobs_list[job_var].assigned = false; //if the car leaves we will un assign the job
 //                   cars_list[c].car_spot_number = -1;
 //                   cars_list[c].busy=false;
					
                }
				
				//RF ? What if the job is complete?
				if (cars_list[c].car_spot_number != -1) {
					int job_var_temp = cars_list[c].job_number;
					jobs_list[job_var_temp].job_duration_remained--;				
				}

                //RF - Logically sound, but we can improve the efficiency here.
                // assigning new cars to the parking lot
                if( c>=2561 && cars_list[c].arrival_time_of_car == i && cars_list[c].car_spot_number == -1 && cars_list[c].turned_away != 1){
                    for (int s=1; s<=2560; s++){
 //                       if (spot_loc[s].occupied == -1 ){
 //                           cars_list[c].car_spot_number = spot_loc[s].spot_number;
 //                           spot_loc[s].occupied_by_car_number=cars_list[c].car_number;
 //                           spot_loc[s].occupied = 1;
 //                           cars_list[c].turned_away = 0;
 //                           cars_list[c].busy=false;
  //                         break;
//                        }
//                        else{
//                            cars_list[c].turned_away = 1;

//                        }

                    }
                }
				
				
				
				

                //VM Migration: if residency time of the car is less than the job durationjob duration of that car; it means that the job may fail
                //so we will migrate the job within 10 mins before the car leaves

				int job_num_var = cars_list[c].job_number;

				bool dummy_flag=false;

				
				if (  jobs_list[job_num_var].job_duration_remained >0  && cars_list[c].job_number != 0 && cars_list[c].car_flag_start_migration == false && cars_list[c].job_has_been_migrated==false && i+START_TIME_MIGRATION >= cars_list[c].departure_time_of_car && cars_list[c].departure_time_of_car >= i && cars_list[c].car_spot_number != -1)   // if the car is migrating
				{
								
									//calculate_congestion(i);
									//calculate_bandwidth();					// This is used to find the bandwidth per min.
									//int spot_num_of_car_migrating_from=cars_list[c].car_spot_number;
									//int cluster_number_of_car_migrating_from=getClusterNumber(spot_num_of_car_migrating_from);
									//int cluster_bandwidth_of_car_migrating_from=cluster_bandwidth[cluster_number_of_car_migrating_from];
									int temp_car_num_migration_to_evaluate = max_residency_not_busy_car(i);
									
									if(temp_car_num_migration_to_evaluate != -1 ){
											int temp_car_num_migration_to= temp_car_num_migration_to_evaluate;		// this is used for migrating the job when we want to pick a car with maximum residency time
											//int spot_num_of_car_migrating_to= cars_list[temp_car_num_migration_to].car_spot_number;
											//int cluster_number_of_car_migrating_to = getClusterNumber(spot_num_of_car_migrating_to);
											//int cluster_bandwidth_of_car_migrating_to=cluster_bandwidth[cluster_number_of_car_migrating_to];
																	
											cars_list[c].car_num_migration_to = temp_car_num_migration_to;
																	
											//lock the car 
											cars_list[temp_car_num_migration_to].busy=true;
											/*
											
											if ( cluster_bandwidth_of_car_migrating_to < cluster_bandwidth_of_car_migrating_from){
												
												 minimum_migration_bandwidth = cluster_bandwidth_of_car_migrating_to;
												
											}
											else{
												
												 minimum_migration_bandwidth = cluster_bandwidth_of_car_migrating_from;
											}
											*/
											
											outMigration << "At Time: "<<i<<"car number: " << c << " with job number:	" << job_num_var << "	will be migrated to car number:	" << temp_car_num_migration_to <<endl;
										//	outMigration<<c<<","<<job_num_var<<","<<temp_car_num_migration_to<<endl;
											dummy_flag=true;

									}	
									
				
				}
			
				
				
				if (dummy_flag==true) 
				{	
					cars_list[c].car_flag_start_migration=true;
					
					//outMigration << "car number	" << c << "	with job number	" << job_num_var << "	will be migrated to car number	" << temp_car_num_migration_to << endl;
					//outMigration << "car number	" << c << "	AFTER DUMMY FLAG cars_list[c].car_flag_start_migration	" << cars_list[c].car_flag_start_migration << endl;
				}
				
				
				// Migration
				
				if(cars_list[c].car_flag_start_migration == true ){
				
					calculate_congestion(i);
					calculate_bandwidth();			
					int spot_num_of_car_migrating_from=cars_list[c].car_spot_number;
					int cluster_number_of_car_migrating_from=getClusterNumber(spot_num_of_car_migrating_from);
					int cluster_bandwidth_of_car_migrating_from=cluster_bandwidth[cluster_number_of_car_migrating_from];
					int temp_car_num_migration_to = cars_list[c].car_num_migration_to;
									
					int spot_num_of_car_migrating_to= cars_list[temp_car_num_migration_to].car_spot_number;
					int cluster_number_of_car_migrating_to = getClusterNumber(spot_num_of_car_migrating_to);
					int cluster_bandwidth_of_car_migrating_to=cluster_bandwidth[cluster_number_of_car_migrating_to];
				
					jobs_list[job_num_var].VM_migration_remained = jobs_list[job_num_var].VM_migration_remained - minimum_migration_bandwidth;

					
					if ( cluster_bandwidth_of_car_migrating_to < cluster_bandwidth_of_car_migrating_from){
												
							 minimum_migration_bandwidth = cluster_bandwidth_of_car_migrating_to;
												
						}
					else{
							
							 minimum_migration_bandwidth = cluster_bandwidth_of_car_migrating_from;
						}
					
					jobs_list[job_num_var].VM_migration_remained = jobs_list[job_num_var].VM_migration_remained - minimum_migration_bandwidth;
					
					if(jobs_list[job_num_var].VM_migration_remained<=0){
						
						//cars_list[c].car_flag_start_migration = false;
						cars_list[c].car_flag_end_migration = true;
					
					}
					
					
					if(cars_list[c].car_flag_end_migration == true && cars_list[c].print_migration_flag_counter==0){
						
						outEndMigration<<"At time: "<<i<<" job number: "<<job_num_var<< " on car number " << c << "	got migrated to	car number: " <<	temp_car_num_migration_to <<endl;
						//outEndMigration<<i<<","<<job_num_var<<","<<c<<","<<temp_car_num_migration_to<<endl;
						cars_list[c].print_migration_flag_counter++;

					}
				
				}
				
				
	

        }	//end of car loop
		
		for(int k=1;k<=40;k++)
				{
						outCongCount<< "Time: " << i <<" For cluster number: "<<k<<"\t"<<cluster_count_migrating[k]<<"Bandwidth is: "<<cluster_bandwidth[k]<<endl;
				}
		

    }
	
	
	for(int j=1;j<=5000;j++)
	{
	      outFileCarParticipation<<cars_list[j].residency_time<<endl;
	}
	for (int jj=0; jj<5000; jj++){
	
	//if(jobs_list[jj].VM_migration_remained >0)
	if (jobs_list[jj].job_flag_start_migration==true && jobs_list[jj].job_flag_end_migration==false){

		outJobFailed<<" VM migration failed: job number: "<<jj<< " on car number " << jobs_list[jj].car_number<<" got failed "<<endl;
	
	}
	
	
	
	
	
	if(jobs_list[jj].job_duration_remained>0 && jobs_list[jj].car_number !=0 ){
	
	//if (jobs_list[jj].job_flag_start_migration==true && jobs_list[jj].job_flag_end_migration==false){
				
		outJobFailed<<" job duration failed: job number: "<<jj<< " on car number " << jobs_list[jj].car_number<<" got failed "<<endl;
				
	}
	
	}
    /*                                                                                        // This is to check the jobs passed and failed for car and its respective output is generated.
        outFileFailed << "These are the jobs that might fail if we don't do the migration" << endl;
        outFilePassJob << "These are the jobs that will possibly succeed" << endl;
        for(int k=1; k<=2560;k++)
        {
			//cout<<"job duration: "<<jobs_list[k].job_duration<<"residency_time: "<<cars_list[k].residency_time<<endl;
            if(jobs_list[k].job_duration > cars_list[k].residency_time)
            {
				jobfailCounter++;
                cars_list[k].display_failed_job_car_details(outFileFailed);

            }
			else
			{
				jobPassCounter++;
				cars_list[k].display_pass_job_car_details(outFilePassJob);

			}

        }


        for (int i=1 ; i <= 5000; i++){

            if (jobs_list[i].migrated_successfully == 2){
                count_migrated_successfully++;
            }

            if (jobs_list[i].migrated_successfully == 3){
                count_failed_to_migrate++;
            }

            if (cars_list[i].turned_away == 1) {
                turned_away_count++;
            outTurnedAway << "car number " << cars_list[i].car_number << " got turned away" << endl;

            }

            if ( jobs_list[i].completed == true){
                jobs_completed++;
            }
        }

        outTurnedAway << "Total Cars turned away : "<<turned_away_count<<endl;
        outTest2 << "Count of jobs migrated successfully " << count_migrated_successfully << endl;
        FailedMigratedJobs <<  "Count of jobs failed to be migrated " << count_failed_to_migrate << endl;
		outFileFailed<< endl <<"Job failed count: "<<jobfailCounter<<endl;
		outFilePassJob<< endl << "Job Pass Count: "<<jobPassCounter<<endl;
		outFilePassJob << endl << "Total of jobs completed: " << jobs_completed << endl;

*/
}



/*
RF - Moved all the following to 
CarModel::GetClusterNumber();
CarModel::GetRegionNumber();
CarModel::GetGroupNumber();
void RegionCenter1()
{

        //For Region1

        for(int i=1;i<=640;i++)
        {
                if( i <= 160)
                {
                        if( i <= 40 )
                        {
                                spot_loc[i].spot_locations(i,1,1,1,1);
                        }

                        if( i > 40  && i <= 80 )
                        {
                                spot_loc[i].spot_locations(i,2,1,1,1);
                        }

                        if( i > 80 && i <= 120 )
                        {
                                spot_loc[i].spot_locations(i,3,1,1,1);
                        }

                        if( i > 120 && i <= 160 )
                        {
                                spot_loc[i].spot_locations(i,4,1,1,1);

                        }
                }

                if( i > 160 && i <= 320)
                {
                        if( i > 160 && i <= 200 )
                        {
                                spot_loc[i].spot_locations(i,5,1,2,1);
                        }

                        if( i > 200  && i <= 240 )
                        {
                                spot_loc[i].spot_locations(i,6,1,2,1);
                        }

                        if( i > 240 && i <= 280 )
                        {
 				spot_loc[i].spot_locations(i,7,1,2,1);
                        }

                        if( i > 280 && i <= 320 )
                        {
                                spot_loc[i].spot_locations(i,8,1,2,1);

                        }
                }

                 if( i > 320 && i <= 480)
                {
                        if( i > 320 && i <= 360 )
                        {
                                spot_loc[i].spot_locations(i,9,1,3,1);
                        }

                        if( i > 360  && i <= 400 )
                        {
                                spot_loc[i].spot_locations(i,10,1,3,1);
                        }

                        if( i > 400 && i <= 440 )
                        {
                                spot_loc[i].spot_locations(i,11,1,3,1);
                        }

                        if( i > 440 && i <= 480 )
                        {
                                spot_loc[i].spot_locations(i,12,1,3,1);

                        }
                }

		if( i > 480 && i <= 640)
                {
                        if( i > 480 && i <= 520 )
                        {
                                spot_loc[i].spot_locations(i,13,1,4,1);
                        }

                        if( i > 520  && i <= 560 )
                        {
                                spot_loc[i].spot_locations(i,14,1,4,1);
                        }

                        if( i > 560 && i <= 600 )
                        {
                                spot_loc[i].spot_locations(i,15,1,4,1);
                        }

                        if( i > 600 && i <= 640 )
                        {
                                spot_loc[i].spot_locations(i,16,1,4,1);

                        }
                }
        }

}

void RegionCenter2()
{

        //For Region1

        for(int i=641;i<=1280;i++)
        {
                if( i <= 800)
                {
                        if( i <= 680 )
                        {
                                spot_loc[i].spot_locations(i,17,2,5,1);
                        }

                        if( i > 680  && i <= 720 )
                        {
                                spot_loc[i].spot_locations(i,18,2,5,1);
                        }

                        if( i > 720 && i <= 760 )
                        {
                                spot_loc[i].spot_locations(i,19,2,5,1);
                        }

                        if( i > 761 && i <= 800 )
                        {
                                spot_loc[i].spot_locations(i,20,2,5,1);

                        }
                }

                if( i > 800 && i <= 960)
                {
                        if( i > 800 && i <= 840 )
                        {
                                spot_loc[i].spot_locations(i,21,2,6,1);
                        }

                        if( i > 840  && i <= 880 )
                        {
                                spot_loc[i].spot_locations(i,22,2,6,1);
                        }

                        if( i > 880 && i <= 920 )
                        {
                                spot_loc[i].spot_locations(i,23,2,6,1);
                        }

                        if( i > 920 && i <= 960 )
                        {
                                spot_loc[i].spot_locations(i,24,2,6,1);

                        }
                }

                 if( i > 960 && i <= 1120)
                {
                        if( i > 960 && i <= 1000 )
                        {
                                spot_loc[i].spot_locations(i,25,2,7,1);
                        }

                        if( i > 1000  && i <= 1040 )
                        {
                                spot_loc[i].spot_locations(i,26,2,7,1);
                        }

                        if( i > 1040 && i <= 1080 )
                        {
                                spot_loc[i].spot_locations(i,27,2,7,1);
                        }

                        if( i > 1080 && i <= 1120 )
                        {
                                spot_loc[i].spot_locations(i,28,2,7,1);

                        }
                }

                if( i > 1120 && i <= 1280)
                {
                        if( i > 1120 && i <= 1160 )
                        {
                                spot_loc[i].spot_locations(i,29,2,8,1);
                        }

                        if( i > 1160  && i <= 1200 )
                        {
                                spot_loc[i].spot_locations(i,30,2,8,1);
                        }

                        if( i > 1200 && i <= 1240 )
                        {
                                spot_loc[i].spot_locations(i,31,2,8,1);
                        }

                        if( i > 1240 && i <= 1280 )
                        {
                                spot_loc[i].spot_locations(i,32,2,8,1);

                        }
                }
        }

}

void RegionCenter3()
{

        //For Region1

        for(int i=1281;i<=1920;i++)
        {
                if( i <= 1440)
                {
                        if( i <= 1320 )
                        {
                                spot_loc[i].spot_locations(i,33,3,9,1);
                        }

                        if( i > 1320  && i <= 1360 )
                        {
                                spot_loc[i].spot_locations(i,34,3,9,1);
                        }

                        if( i > 1360 && i <= 1400 )
                        {
                                spot_loc[i].spot_locations(i,35,3,9,1);
                        }

                        if( i > 1400 && i <= 1440 )
                        {
                                spot_loc[i].spot_locations(i,36,3,9,1);

                        }
                }

                if( i > 1440 && i <= 1600)
                {
                        if( i > 1440 && i <= 1480 )
                        {
                                spot_loc[i].spot_locations(i,37,3,10,1);
                        }

                        if( i > 1480  && i <= 1520 )
                        {
                                spot_loc[i].spot_locations(i,38,3,10,1);
                        }

                        if( i > 1520 && i <= 1560 )
                        {
                                spot_loc[i].spot_locations(i,39,3,10,1);
                        }

                        if( i > 1560 && i <= 1600 )
                        {
                                spot_loc[i].spot_locations(i,40,3,10,1);

                        }
                }

                 if( i > 1600 && i <= 1760)
                {
                        if( i > 1600 && i <= 1640 )
                        {
                                spot_loc[i].spot_locations(i,41,3,11,1);
                        }

                        if( i > 1640  && i <= 1680 )
                        {
                                spot_loc[i].spot_locations(i,42,3,11,1);
                        }

                        if( i > 1680 && i <= 1720 )
                        {
                                spot_loc[i].spot_locations(i,43,3,11,1);
                        }

                        if( i > 1720 && i <= 1760 )
                        {
                                spot_loc[i].spot_locations(i,44,3,11,1);

                        }
                }

                if( i > 1760 && i <= 1920)
                {
                        if( i > 1760 && i <= 1800 )
                        {
                                spot_loc[i].spot_locations(i,45,3,12,1);
                        }

                        if( i > 1800  && i <= 1840 )
                        {
                                spot_loc[i].spot_locations(i,46,3,12,1);
                        }

                        if( i > 1840 && i <= 1880 )
                        {
                                spot_loc[i].spot_locations(i,47,3,12,1);
                        }

                        if( i > 1880 && i <= 1920 )
                        {
                                spot_loc[i].spot_locations(i,48,3,12,1);

                        }
                }
        }

}

void RegionCenter4()
{

        //For Region1cars_list[i].car_spot_number

        for(int i=1921;i<=2560;i++)
        {
                if( i <= 2080)
                {
                        if( i <= 1960 )
                        {
                                spot_loc[i].spot_locations(i,49,4,13,1);
                        }

                        if( i > 1960  && i <= 2000 )
                        {
                                spot_loc[i].spot_locations(i,50,4,13,1);
                        }

                        if( i > 2000 && i <= 2040 )
                        {
                                spot_loc[i].spot_locations(i,51,4,13,1);
                        }

                        if( i > 2040 && i <= 2080 )
                        {
                                spot_loc[i].spot_locations(i,52,4,13,1);

                        }
                }

                if( i > 2080 && i <= 2240)
                {
                        if( i > 2080 && i <= 2120 )
                        {
                                spot_loc[i].spot_locations(i,53,4,14,1);
                        }

                        if( i > 2120  && i <= 2160 )
                        {
                                spot_loc[i].spot_locations(i,54,4,14,1);
                        }

                        if( i > 2160 && i <= 2200 )
                        {
                                spot_loc[i].spot_locations(i,55,4,14,1);
                        }

                        if( i > 2200 && i <= 2240 )
                        {
                                spot_loc[i].spot_locations(i,56,4,14,1);

                        }
                }

                 if( i > 2240 && i <= 2400)
                {
                        if( i > 2240 && i <= 2280 )
                        {
                                spot_loc[i].spot_locations(i,57,4,15,1);
                        }

                        if( i > 2280  && i <= 2320 )
                        {
                                spot_loc[i].spot_locations(i,58,4,15,1);
                        }

                        if( i > 2320 && i <= 2360 )
                        {
                                spot_loc[i].spot_locations(i,59,4,15,1);
                        }

                        if( i > 2360 && i <= 2400 )
                        {
                                spot_loc[i].spot_locations(i,60,4,15,1);

                        }
                }

                if( i > 2400 && i <= 2560)
                {
                        if( i > 2400 && i <= 2440 )
                        {
                                spot_loc[i].spot_locations(i,61,4,16,1);
                        }

                        if( i > 2440  && i <= 2480 )
                        {
                                spot_loc[i].spot_locations(i,62,4,16,1);
                        }

                        if( i > 2480 && i <= 2520 )
                        {
                                spot_loc[i].spot_locations(i,63,4,16,1);
                        }

                        if( i > 2520 && i <= 2560 )
                        {
                                spot_loc[i].spot_locations(i,64,4,16,1);

                        }
                }
        }

}
*/