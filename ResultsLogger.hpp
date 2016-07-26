//File:         ResultsLogger.hpp
//Description: 	Provides results logging to the application
//   Initialize() - used to initialize the results logger with configuration options set within the configuration Model.
//   *results - Used to output logging data


#ifndef __RESULTSLOGGER_HPP__
#define __RESULTSLOGGER_HPP__

#include <fstream>
#include "Configuration.hpp"

class ResultsLogger
{
    //private:
//	  Configuration _configuration;
//      static std::ostream * throwaway;

	public:
	  static std::ofstream results;
	  static std::ofstream results_carsInParkingLot;
	  static std::ofstream results_jobsInParkingLot;
	  static std::ofstream results_bandwidth;

      void Initialize();
};

#endif
