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
//    JobArrival_Static -
//    JobArrival_Static_Value -
//    JobArrival_Poisson -
//    JobArrival_Poisson_Lambda -
//
//    JobLength_Static -
//    JobLength_Static_Value -
//    JobLength_Normal -
//    JobLength_Normal_Mean -
//    JobLength_Normal_STDev -
//
//    JobVMSize_Static -
//    JobVMSize_Static_Value -
//    JobVMSize_Normal -
//    JobVMSize_Normal_Mean -
//    JobVMSize_Normal_STDev -

#include <sstream>

#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__



class Configuration
{
  public:

   //Program level configurations
   //  These are basic configurations that do not affect the logic
   static int LogLevel;
   static bool PauseAtEndOfCode;

   //Time loop level configuration
   //  The affect the time loop
   static int MaxTime;
   static int TimeStep;

   //Network configuration
   //  These affect the network
   static double BandwidthPerSecondForCluster;

   static int NumberOfParkingSpaces;

   //Migration configuration
   //  These affect the migrations
   static int VMMigrationOffset;
   static int NumberOfDataBackupsRequired;
   static bool DataMigrationType_Random;

   //Car configuration
   static bool CarArrival_FromFile;
   static bool CarArrival_Static;
   static int CarArrival_Static_Value;
   static bool CarArrival_Poisson;
   static double CarArrival_Poisson_Lambda;

   static bool CarDeparture_Static;
   static int CarDeparture_Static_Value;
   static bool CarDeparture_Exponential;
   static double CarDeparture_Exponential_Lambda;


   //Job configuration
   static bool JobArrival_Static;
   static int JobArrival_Static_Value;
   static bool JobArrival_Poisson;
   static double JobArrival_Poisson_Lambda;

   static bool JobLength_Static;
   static int JobLength_Static_Value;
   static bool JobLength_Normal;
   static double JobLength_Normal_Mean;
   static double JobLength_Normal_STDev;

   static bool JobVMSize_Static;
   static int JobVMSize_Static_Value;
   static bool JobVMSize_Normal;
   static double JobVMSize_Normal_Mean;
   static double JobVMSize_Normal_STDev;



   void ReadFromFile();
   bool ConvertToBool(std::string &data);
   int ConvertToInt(std::string &data);
   double ConvertToDouble(std::string &data);

};



#endif
