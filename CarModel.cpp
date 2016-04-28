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


//Initialize the carmap and empty spaces structures
void CarModel::Initialize()
{
	initializing = true;
	for (int i=0; i < _configuration.NumberOfParkingSpaces; i++)
	{
		emptySpaces.push_back(i);		
	}

	for (int i=0; i < _configuration.NumberOfParkingSpaces; i++)
	{
		CreateNewCar();
	}
	
	
	initializing = false;
}




//Creates a new car if there is an empty space for a new car
//Returns false if a new car was not created
//Returns true is a new car was created
bool CarModel::CreateNewCar()
{
//	Check is emptySpaces is empty, if empty, do not create a car
//	randomly select a parking space to populate
//	create the car, populate details
//	remove the space from the empty slot

  
  //If there are no empty spaces, return false;
  if (emptySpaces.empty())
  {
    if (!initializing)
	  _carResidencyDistributionModel.generateNext();	  
 	//TODO: Update Statistics
	return false;		
  }
 	 
  int randomEmptyIndex = _random.GetNextInt(emptySpaces.size());
  int randomEmptySpace = 0;
  //Get the empty space at the randomEmptyIndexth place in the list
  std::list<int>::iterator it;
  int counter = 0;
  for(it = emptySpaces.begin(); it != emptySpaces.end(); it++) 
  {
	  if (counter == randomEmptyIndex)
	  {
		  randomEmptySpace = *it;
		  break;
	  }
	  
	  counter++;
  }
  
  
  
  Car newCar;
  newCar.car_spot_number = randomEmptySpace;  
  newCar.arrival_time_of_car = _time.getTime();
  if (initializing)
  {
    //This is a poor way to initialize the parkinglot.
    newCar.departure_time_of_car = 1440;
  }
  else
  {
    newCar.departure_time_of_car = _carResidencyDistributionModel.getNextDeparture();
    _carResidencyDistributionModel.generateNext();	  
  }
  newCar.busy = false;
  
  carmap[randomEmptySpace] = newCar;
  
  emptySpaces.remove(randomEmptySpace);
  
  std::cout << "Car in spot " << randomEmptySpace << " has arrived" << std::endl;

}

void CarModel::HandleIncomingVehicles()
{
	while (_time.getTime() >= _carResidencyDistributionModel.getNextArrival())
	{
		CreateNewCar();		
	}	
}

void CarModel::HandleLeavingVehicles()
{
//  Loop through all vehicles and determine if it is leaving
//	add the space to the empty space list
//	update statistics
//	remove the car from the carmap
	
  std::map<int, Car>::iterator it;
  for(it = carmap.begin(); it != carmap.end(); it++) 
  {
    Car leavingCar = it->second;
    int leavingCarSpace = it->first; 
    //Check if car has left or is leaving
    if (leavingCar.departure_time_of_car <= _time.getTime())
    {
  	  std::cout << "Car in spot " << leavingCarSpace << " is leaving" << std::endl;
	  emptySpaces.push_back(leavingCarSpace);
  	  //** Need to save off some statistics here!
  	  carmap.erase(leavingCarSpace);	 
    }
  }  
}


int CarModel::getClusterNumber(int spotId)
{
	return spotId % 40;
}
int CarModel::getRegionNumber(int spotId)
{
	return spotId % 160;
}
int CarModel::getGroupNumber(int spotId)
{
	return spotId % 640;
}
