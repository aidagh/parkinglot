//File:         Results Logger.cpp
//Description: 	Provides results logging to the application

#include "ResultsLogger.hpp"
#include <fstream>

std::ofstream ResultsLogger::results; //= NULL;//("Results.out");

void ResultsLogger::Initialize()
{
    results.open("Results.out", std::ofstream::out | std::ofstream::app);
}



