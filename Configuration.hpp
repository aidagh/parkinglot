//File:         Configuration.hpp
//Description: 	Provides configuration data to the application
//  ReadFromFile - Sets the configuration options from a file: config.in
//  Options:
//    LogLevel - Set the level of logging for the application: 0-Trace, 1-Debug, 2-Warn
//    MaxTime - Sets the maximum Time of the time loop.
//    TimeStep - Set the amount of time each step will be incremented in the time loop.
//    BandwidthPerSecondForCluster -
//    NumberOfParkingSpaces -
//    VMMigrationOffset -
//    CarArrival_FromFile -
//    CarArrival_Static -
//    CarArrival_Static_Value -
//    CarArrival_Poisson -
//    CarArrival_Poisson_Lambda -
//    CarDeparture_Static -
//    CarDeparture_Static_Value -
//    CarDeparture_Exponential -
//    CarDeparture_Exponential_Lambda -

#include <sstream>

#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__



class Configuration
{
  public:
   static int LogLevel;
  
   static int MaxTime;
   static int TimeStep;
   static double BandwidthPerSecondForCluster;
   static int NumberOfParkingSpaces;
   
   
   static int VMMigrationOffset;
   
   static bool CarArrival_FromFile;
   static bool CarArrival_Static;
   static int CarArrival_Static_Value;   
   static bool CarArrival_Poisson;
   static double CarArrival_Poisson_Lambda;

   static bool CarDeparture_Static;
   static int CarDeparture_Static_Value;   
   static bool CarDeparture_Exponential;
   static double CarDeparture_Exponential_Lambda;

   
   void ReadFromFile();
   bool ConvertToBool(std::string &data);   
   int ConvertToInt(std::string &data);
   double ConvertToDouble(std::string &data);

};

int Configuration::LogLevel = 0;
int Configuration::MaxTime = 100; 
int Configuration::TimeStep = 1; 
double Configuration::BandwidthPerSecondForCluster = .125; 
int Configuration::NumberOfParkingSpaces = 10;

int Configuration::VMMigrationOffset = 10;

bool Configuration::CarArrival_FromFile = false;
bool Configuration::CarArrival_Static = true;
int Configuration::CarArrival_Static_Value = 10;
bool Configuration::CarArrival_Poisson = false;
double Configuration::CarArrival_Poisson_Lambda = 0.1;

bool Configuration::CarDeparture_Static = true;
int Configuration::CarDeparture_Static_Value = 25;
bool Configuration::CarDeparture_Exponential = false;
double Configuration::CarDeparture_Exponential_Lambda = 0.1;


#endif