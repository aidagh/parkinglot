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



//Class will be updated to handle a seed so that many runs can be performed with a different seed.
class Random
{
  public:

  int GetNextInt(int max);
  double GetNextDouble(double max);
  

};

int Random::GetNextInt(int max)
{
  return rand() % max;
}

double Random::GetNextDouble(double max)
{
  return ((double)rand() / (RAND_MAX)) * max;
}

