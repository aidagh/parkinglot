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
//    CarDeparture_Exponential_Mean -
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


#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#include <sstream>

class Configuration
{
  public:

    static char* ConfigFileName;
    static int Seed;
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
   static double BandwidthPerMinuteForClusterInMegaBytes;
   static double BandwidthPerMinuteForGroupInMegaBytes;
   static double BandwidthPerMinuteForRegionInMegaBytes;
   static double BandwidthPerMinuteForDataCenterInMegaBytes;

   static int NumberOfParkingSpaces;

   //Job configuration
   //  These affect the jobs and tasks
   static int MaxVehicleUtilization;
   static int MaxJobsInInitialSetup;
   static int NumberTasksPerJob;
   static bool TaskScheme_AlternateProcessAndDataMigrate;


   //Migration configuration
   //  These affect the migrations
   static int VMMigrationOffset;
   static int NumberOfDataBackupsRequired;
   static bool DataMigrationType_Random;
   static bool DataMigrationType_TwoClusterOneGroup_Random;

   //Car configuration
   static bool CarArrival_FromFile;
   static bool CarArrival_Static;
   static double CarArrival_Static_Value;
   static bool CarArrival_Poisson;
   static double CarArrival_Poisson_Lambda;

   static bool CarDeparture_Static;
   static double CarDeparture_Static_Value;
   static bool CarDeparture_Exponential;
   static double CarDeparture_Exponential_Mean;


   //Job configuration
   static bool JobArrival_Static;
   static double JobArrival_Static_Value;
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

   static bool JobDataSize_Static;
   static int JobDataSize_Static_Value;
   static bool JobDataSize_Normal;
   static double JobDataSize_Normal_Mean;
   static double JobDataSize_Normal_STDev;



   void SetConfigFile(char* filename);
   void SetSeed(int seed);
   void ReadFromFile();
   bool ConvertToBool(std::string &data);
   int ConvertToInt(std::string &data);
   double ConvertToDouble(std::string &data);
   void PrintConfiguration();
   void WriteConfigSettings();
};



#endif
