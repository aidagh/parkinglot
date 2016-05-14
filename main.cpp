//File:         main.cpp
//Project name: To simulate the datacenter for a vehicle parking lot in an Airport.
//Description:  The goal of the project is to simulate a datacenter implemented on the cars in the parking lot of a medium sized airport.
//              As cars arrive and depart randomly, the challenge facing the implementation of the datacenter is to maintain high availability
//              and reliability in the face of the dynamically changing resources. Tradeoffs will be identified and analyzed and several
//              possible solutions will be contrasted. The project is deliberately open ended, allowing each student to add performance-enhancing
//              "bells and whistles".



//TODO: Review if all the following are needed here
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <map>
#include <list>
#include <queue>



#include "Logger.hpp"
//#include "Logger.cpp"
#include "TimeModel.hpp"
//#include "Random.hpp"
#include "Configuration.hpp"
//#include "Configuration.cpp"
//#include "Car.hpp"
//#include "Car.cpp"
//#include "MigrationJob.hpp"
//#include "Job.hpp"
//#include "Job.cpp"
//#include "NetworkModel.hpp"
//#include "NetworkModel.cpp"
#include "CarResidencyDistributionModel.hpp"
//#include "CarResidencyDistributionModel.cpp"
//#include "DistributionFactory/CarArrivalDistributionFactory.hpp"
//#include "DistributionFactory/CarArrivalDistributionFactory.cpp"
//#include "DistributionFactory/CarDepartureDistributionFactory.hpp"
//#include "DistributionFactory/CarDepartureDistributionFactory.cpp"
#include "JobDistributionModel.hpp"
//#include "JobDistributionModel.cpp"
//#include "DistributionFactory/JobArrivalDistributionFactory.hpp"
//#include "DistributionFactory/JobArrivalDistributionFactory.cpp"
//#include "DistributionFactory/JobLengthDistributionFactory.hpp"
//#include "DistributionFactory/JobLengthDistributionFactory.cpp"
//#include "DistributionFactory/JobVMSizeDistributionFactory.hpp"
//#include "DistributionFactory/JobVMSizeDistributionFactory.cpp"
//#include "StatisticsModel.hpp"
//#include "StatisticsModel.cpp"

#include "CarModel.hpp"
//#include "CarModel.cpp"
#include "JobModel.hpp"
//#include "JobModel.cpp"



Configuration _configuration;
CarResidencyDistributionModel _carResidencyDistributionModel;
JobDistributionModel _jobDistributionModel;
CarModel _carModel;
TimeModel _timeModel;
JobModel _jobModel;
Logger _log;





int main()
{
	_log.Initialize();
	*_log.info << "Showing Info Logs" << std::endl;
	*_log.debug << "Showing Debug Logs" << std::endl;
	*_log.trace << "Showing Trace Logs" << std::endl;


	_carResidencyDistributionModel.Initialize();
	_jobDistributionModel.Initialize();
	_carModel.Initialize();
	_timeModel.initialize();


	while (_timeModel.getTime() < _configuration.MaxTime)
	{
	  *_log.info << "Time: " << _timeModel.getTime() << std::endl;
      _carModel.HandleCars();
	  _jobModel.HandleJobs();

      _carModel.PrintVehicleInfo();
	  _timeModel.increment();

//	  std::cin.get();
	}


	if (_configuration.PauseAtEndOfCode)
    {
        std::cin.get();
    }

}

