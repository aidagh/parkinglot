//File:         Results Logger.cpp
//Description: 	Provides results logging to the application

#include "ResultsLogger.hpp"
#include <fstream>

std::ofstream ResultsLogger::results; //= NULL;//("Results.out");
std::ofstream ResultsLogger::results_carsInParkingLot;
std::ofstream ResultsLogger::results_jobsInParkingLot;

void ResultsLogger::Initialize()
{
    results.open("Results.out", std::ofstream::out | std::ofstream::app);
    results_carsInParkingLot.open("ResultsCarsInParkingLot.out", std::ofstream::out | std::ofstream::app);
    results_jobsInParkingLot.open("ResultsJobsInParkingLot.out", std::ofstream::out | std::ofstream::app);
}



