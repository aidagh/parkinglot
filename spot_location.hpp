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

#ifndef __SPOT_LOCATION_HPP__
#define __SPOT_LOCATION_HPP__



//This class includes all information about the parking spots and also it keeps track of whether parking spot is occupied or not.
class spot_location
{
  public: 
    int spot_number;
    int cluster_number;
    int region_number;
    int group_center_number;
    int occupied;
    int occupied_by_car_number;
    
	void spot_locations(int sno, int cno, int rno, int gcnumber, int occup);
	void display_spot_information(std::ofstream& outFile);
	
};

#endif