//File:         CarModel.cpp
//Description:

#include "CarModel.hpp"


std::map<int, Car*> CarModel::carmap;
std::list<int> CarModel::emptySpaces;
bool CarModel::initializing = false;

//Initialize the carmap and empty spaces structures
void CarModel::Initialize()
{
	initializing = true;
	for (int i=1; i <= _configuration.NumberOfParkingSpaces; i++)
	{
		emptySpaces.push_back(i);
	}

	for (int i=1; i <= _configuration.NumberOfParkingSpaces; i++)
	{
		createNewCar();
	}

	initializing = false;
}


void CarModel::HandleCars()
{
  HandleDepartingVehicles();
  HandleIncomingVehicles();
}


//Creates a new car if there is an empty space for a new car
//Returns false if a new car was not created
//Returns true is a new car was created
void CarModel::createNewCar()
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
	return;
  }


  int randomEmptyIndex = 0; //_random.GetNextInt(emptySpaces.size());
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


  Car * newCar = new Car();
  newCar->car_spot_number = randomEmptySpace;
  newCar->car_cluster_number = getClusterNumber(randomEmptySpace);
  newCar->car_group_number = getGroupNumber(randomEmptySpace);
  newCar->car_region_number = getRegionNumber(randomEmptySpace);
  newCar->arrival_time_of_car = _time.getTime();

  if (initializing)
  {
    //This is a poor way to initialize the parkinglot.
    newCar->departure_time_of_car = 40;
  }
  else
  {
    newCar->departure_time_of_car = _carResidencyDistributionModel.getNextDeparture();
    _carResidencyDistributionModel.generateNext();
  }

  carmap[randomEmptySpace] = newCar;
  emptySpaces.remove(randomEmptySpace);
  *_log.info << "Car in spot " << randomEmptySpace << ", and cluster "
                << newCar->car_cluster_number << ", group "
                << newCar->car_group_number << ", region "
                << newCar->car_region_number << " has arrived" << std::endl;

}


void CarModel::HandleIncomingVehicles()
{
	while (_time.getTime() >= _carResidencyDistributionModel.getNextArrival())
	{
		createNewCar();
	}
}


//For a car that is migrating, choose the car to migrate to
Car * CarModel::GetVMMigrationToVehicle(Car* FromCar)
{
  //Loop through and find the latest departing vehicle that currently is not running a job.
  //ToDo: This needs to consider cluster
  Car* latestDepartingCar = NULL;
  int latestDepartureTime = 0;
  std::map<int, Car*>::iterator it;

  for(it = carmap.begin(); it != carmap.end(); it++)
  {
     if (it->second->canAcceptJob() && it->second->departure_time_of_car > latestDepartureTime)
	 {
		 latestDepartingCar = it->second;
		 latestDepartureTime = latestDepartingCar->departure_time_of_car;
		 *_log.trace << "Car " << it->first << " can accept job, leaving " << latestDepartingCar->departure_time_of_car << std::endl;
	 }
  }

  return latestDepartingCar;
}


void CarModel::handleVehicleDepartingNOW()
{
//  Loop through all vehicles and determine if it is leaving NOW
//	  add the space to the empty space list
//	  update statistics
//	  remove the car from the carmap
  std::list<int> carsToErase;
  JobModel _jobModel;
  std::map<int, Car*>::iterator it;
  for(it = carmap.begin(); it != carmap.end(); it++)
  {
    Car leavingCar = *(it->second);
    int leavingCarSpace = it->first;

    //Check if car has left or is leaving
    if (leavingCar.departure_time_of_car <= _time.getTime())
    {
	  if (leavingCar.job != NULL)
	    _jobModel.CancelJob(leavingCarSpace);

  	  *_log.info << "Car in spot " << leavingCarSpace << " is leaving NOW" << std::endl;
	  emptySpaces.push_back(leavingCarSpace);
  	  //** Need to save off some statistics here!

	  carsToErase.push_back(leavingCarSpace);
    }
  }

  std::list<int>::iterator itCarsToErase;
  for(itCarsToErase = carsToErase.begin(); itCarsToErase != carsToErase.end(); itCarsToErase++)
  {
  	  carmap.erase(*itCarsToErase);
  }
}


void CarModel::handleVehicleDepartingSOON()
{
//  Loop through all vehicles and determine if it is leaving SOON
//	  Mark the vehicle as migrating - setup the job/car to migrate
//	  update statistics

  JobModel _jobModel;

  std::map<int, Car*>::iterator it;
  for(it = carmap.begin(); it != carmap.end(); it++)
  {
    Car * leavingCar = it->second;
    int leavingCarSpace = it->first;

	//Check if car is leaving soon, and has a VM
	bool carHasAMigratableJob = (leavingCar->job != NULL) && (leavingCar->job->jobStatus == Processing || leavingCar->job->jobStatus == DataMigrating);
    if (carHasAMigratableJob && leavingCar->departure_time_of_car <= _time.getTime() + _configuration.VMMigrationOffset )
    {
  	  *_log.info << "Starting Migration of Car in spot " << leavingCarSpace << " " << std::endl;

      //1. Choose car to migrate to
	  //2. Set Migration to
	  //3. Stop Job Processing / Data Migration
	  leavingCar->job->jobStatus = VMMigrating;

	  Car * carToMigrateTo = GetVMMigrationToVehicle(it->second);

	  if (carToMigrateTo != NULL)
	  {
        _jobModel.SetupVMMigration(leavingCar, carToMigrateTo) ;

	    //emptySpaces.push_back(leavingCarSpace);
  	    //** Need to save off some statistics here!
  	    //carmap.erase(leavingCarSpace);
	  }
	  else
	  {
		  //There is no car to migrate to..  Currently, the code will just try again next minute.
	  }
    }
  }
}


//This method handles the following two cases:
//  1. Handle cars that are departing NOW
//     a. remove the vehicle, update statistics, remove car from carmap
//  2. Handle cars that are departing SOON
//     b. attempt to Migrate the VM if that vehicle is departing soon.
void CarModel::HandleDepartingVehicles()
{
	handleVehicleDepartingNOW();
	handleVehicleDepartingSOON();
}


//Assign Job returns a pointer to the car it is assigned to.
Car * CarModel::AssignJob(Job* job)
{
  std::map<int, Car*>::iterator it;

  for(it = carmap.begin(); it != carmap.end(); it++)
  {
	 if (it->second->job != NULL)
	 {
		 *_log.debug << "Space:" << it->first << " is busy with job: " << it->second->job->job_number << std::endl;
	 }
	 else
	 {
		 *_log.debug << "Space:" << it->first << " is not busy " << std::endl;
	 }
  }

  for(it = carmap.begin(); it != carmap.end(); it++)
  {
    Car* car = it->second;
    int carSpace = it->first;
    //Check if car has a job or is getting a job migrated
    if (car->canAcceptJob())
    {
  	  *_log.info << "Car in spot " << carSpace << " is assigned Job " << job->job_number << std::endl;
	  car->job_number = job->job_number;
	  car->job = job;

	  return car;
	  //break;
    }
  }

  *_log.info << "Job cannot be assigned to any cars :" << job->job_number << std::endl;

  return NULL;
}


std::list<Car*> CarModel::AssignDataMigrationCars(Job* job)
{
    std::list<Car*> MigrationSet;
    Random random;

    //random assignment
    //loop through all Cars, randomly pick "n" to accept the data migration

    if (_configuration.DataMigrationType_Random)
    {
        for (int i=0; i<_configuration.NumberOfDataBackupsRequired; i++)
        {
            //duplicates do not matter for this simple DataMigrationType
            int dataMigrationCar = random.GetNextInt(carmap.size());
            //iterate to the dataMigrationCar'th car in the carmap and assign it as a migration car.

            std::map<int, Car*>::iterator it;

            int j = 0;
            for(it = carmap.begin(); it != carmap.end(); it++)
            {
                j++;
                if (j == dataMigrationCar)
                {
                    MigrationSet.push_back(it->second);
                }
            }
        }
    }
    else
    {
        *_log.info << "No DataMigrationType Setup" << std::endl;
    }

    return MigrationSet;
}


void CarModel::PrintVehicleInfo()
{
  std::map<int, Car*>::iterator it;

  for(it = carmap.begin(); it != carmap.end(); it++)
  {
      it->second->printCarDetails(true, "");
  }
}


int CarModel::getClusterNumber(int spotId)
{
	if(spotId%40 == 0) return (spotId/40);

	else return ((spotId/40)+1);
}

int CarModel::getGroupNumber(int spotId)
{
    if(spotId%160 == 0) return (spotId/160);

	else return ((spotId/160)+1);
}

int CarModel::getRegionNumber(int spotId)
{

    if(spotId%640 == 0) return (spotId/640);

	else return ((spotId/640)+1);

}

