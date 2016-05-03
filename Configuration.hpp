
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
   
   void ReadFromFile();
   bool ConvertToBool(std::string &data);   
   int ConvertToInt(std::string &data);
   double ConvertToDouble(std::string &data);

};

int Configuration::LogLevel = 2;
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



#endif