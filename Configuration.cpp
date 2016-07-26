//File:         Configuration.cpp
//Description: 	Provides configuration data to the application

//#include <sstream>
#include <iostream>

#include "Configuration.hpp"
#include "ResultsLogger.hpp"

char* Configuration::ConfigFileName = "config.in";

int Configuration::LogLevel = 0;
bool Configuration::PauseAtEndOfCode = true;
int Configuration::MaxTime = 100;
int Configuration::TimeStep = 1;
double Configuration::BandwidthPerMinuteForClusterInMegaBytes = 75;
double Configuration::BandwidthPerMinuteForWiredLinksInMegaBytes = 7500;
int Configuration::NumberOfParkingSpaces = 2560;

int Configuration::MaxVehicleUtilization = 50;
int Configuration::MaxJobsInInitialSetup = 5;
int Configuration::NumberTasksPerJob = 4;
bool Configuration::TaskScheme_AlternateProcessAndDataMigrate = true;


int Configuration::VMMigrationOffset = 10;
int Configuration::NumberOfDataBackupsRequired = 3;
bool Configuration::DataMigrationType_Random = false;
bool Configuration::DataMigrationType_TwoClusterOneGroup_Random = true;

bool Configuration::CarArrival_FromFile = false;
bool Configuration::CarArrival_Static = true;
double Configuration::CarArrival_Static_Value = 5;
bool Configuration::CarArrival_Poisson = false;
double Configuration::CarArrival_Poisson_Lambda = 0.1;

bool Configuration::CarDeparture_Static = true;
double Configuration::CarDeparture_Static_Value = 25;
bool Configuration::CarDeparture_Exponential = false;
double Configuration::CarDeparture_Exponential_Mean = 10;


bool Configuration::JobArrival_Static = true;
double Configuration::JobArrival_Static_Value = 10;
bool Configuration::JobArrival_Poisson = false;
double Configuration::JobArrival_Poisson_Lambda = .05;

bool Configuration::JobLength_Static = true;
int Configuration::JobLength_Static_Value = 5;
bool Configuration::JobLength_Normal = false;
double Configuration::JobLength_Normal_Mean = 20;
double Configuration::JobLength_Normal_STDev = 5;

bool Configuration::JobVMSize_Static = true;
int Configuration::JobVMSize_Static_Value = 5;
bool Configuration::JobVMSize_Normal = false;
double Configuration::JobVMSize_Normal_Mean = 10;
double Configuration::JobVMSize_Normal_STDev = 3;

bool Configuration::JobDataSize_Static = true;
int Configuration::JobDataSize_Static_Value = 5;
bool Configuration::JobDataSize_Normal = false;
double Configuration::JobDataSize_Normal_Mean = 10;
double Configuration::JobDataSize_Normal_STDev = 3;


void Configuration::SetConfigFile(char * filename)
{
    ConfigFileName = filename;
}


void Configuration::ReadFromFile()
{
  std::ifstream file;
  std::string line;
  file.open(ConfigFileName, std::fstream::in);
  while (std::getline(file, line))
  {
    std::string left = line.substr(0, line.find("="));
    std::string right = line.substr(line.find("=")+1, line.size() - line.find("="));

    if (left == "LogLevel")
    {
      LogLevel = ConvertToInt(right);
    }
    if (left == "MaxTime")
    {
      MaxTime = ConvertToInt(right);
    }
    if (left == "TimeStep")
    {
      TimeStep = ConvertToInt(right);
    }
    if (left == "BandwidthPerMinuteForClusterInMegaBytes")
    {
      BandwidthPerMinuteForClusterInMegaBytes = ConvertToDouble(right);
    }
    if (left == "BandwidthPerMinuteForWiredLinksInMegaBytes")
    {
      BandwidthPerMinuteForWiredLinksInMegaBytes = ConvertToDouble(right);
    }
    if (left == "NumberOfParkingSpaces")
    {
      NumberOfParkingSpaces = ConvertToInt(right);
    }

    if (left == "MaxVehicleUtilization")
    {
      MaxVehicleUtilization = ConvertToInt(right);
    }
    if (left == "MaxJobsInInitialSetup")
    {
      MaxJobsInInitialSetup = ConvertToInt(right);
    }

    if (left == "NumberTasksPerJob")
    {
      NumberTasksPerJob = ConvertToInt(right);
    }
    if (left == "TaskScheme_AlternateProcessAndDataMigrate")
    {
      TaskScheme_AlternateProcessAndDataMigrate = ConvertToBool(right);
    }
    if (left == "VMMigrationOffset")
    {
      VMMigrationOffset = ConvertToInt(right);
    }
    if (left == "NumberOfDataBackupsRequired")
    {
      NumberOfDataBackupsRequired = ConvertToInt(right);
    }
    if (left == "DataMigrationType_Random")
    {
      DataMigrationType_Random = ConvertToBool(right);
    }
    if (left == "DataMigrationType_TwoClusterOneGroup_Random")
    {
      DataMigrationType_TwoClusterOneGroup_Random = ConvertToBool(right);
    }

    if (left == "CarArrival_FromFile")
	{
	  CarArrival_FromFile = ConvertToBool(right);
	}
    if (left == "CarArrival_Static")
	{
	  CarArrival_Static = ConvertToBool(right);
	}
    if (left == "CarArrival_Static_Value")
	{
	  CarArrival_Static_Value = ConvertToDouble(right);
	}
    if (left == "CarArrival_Poisson")
	{
	  CarArrival_Poisson = ConvertToBool(right);
	}
    if (left == "CarArrival_Poisson_Lambda")
	{
	  CarArrival_Poisson_Lambda = ConvertToDouble(right);
	}
    if (left == "CarDeparture_Static")
	{
	  CarDeparture_Static = ConvertToBool(right);
	}
    if (left == "CarDeparture_Static_Value")
	{
	  CarDeparture_Static_Value = ConvertToDouble(right);
	}
    if (left == "CarDeparture_Exponential")
	{
	  CarDeparture_Exponential = ConvertToBool(right);
	}
    if (left == "CarDeparture_Exponential_Mean")
	{
	  CarDeparture_Exponential_Mean = ConvertToDouble(right);
	}

    if (left == "JobArrival_Static")
    {
        JobArrival_Static = ConvertToBool(right);
    }
    if (left == "JobArrival_Static_Value")
    {
        JobArrival_Static_Value = ConvertToDouble(right);
    }
    if (left == "JobArrival_Poisson")
    {
        JobArrival_Poisson = ConvertToBool(right);
    }
    if (left == "JobArrival_Poisson_Lambda")
    {
        JobArrival_Poisson_Lambda = ConvertToDouble(right);
    }

    if (left == "JobLength_Static")
    {
        JobLength_Static = ConvertToBool(right);
    }
    if (left == "JobLength_Static_Value")
    {
        JobLength_Static_Value = ConvertToInt(right);
    }
    if (left == "JobLength_Normal")
    {
        JobLength_Normal = ConvertToBool(right);
    }
    if (left == "JobLength_Normal_Mean")
    {
        JobLength_Normal_Mean = ConvertToDouble(right);
    }
    if (left == "JobLength_Normal_STDev")
    {
        JobLength_Normal_STDev = ConvertToDouble(right);
    }



    if (left == "JobVMSize_Static")
    {
        JobVMSize_Static = ConvertToBool(right);
    }
    if (left == "JobVMSize_Static_Value")
    {
        JobVMSize_Static_Value = ConvertToInt(right);
    }
    if (left == "JobVMSize_Normal")
    {
        JobVMSize_Normal = ConvertToBool(right);
    }
    if (left == "JobVMSize_Normal_Mean")
    {
        JobVMSize_Normal_Mean = ConvertToDouble(right);
    }
    if (left == "JobVMSize_Normal_STDev")
    {
        JobVMSize_Normal_STDev = ConvertToDouble(right);
    }


    if (left == "JobDataSize_Static")
    {
        JobDataSize_Static = ConvertToBool(right);
    }
    if (left == "JobDataSize_Static_Value")
    {
        JobDataSize_Static_Value = ConvertToInt(right);
    }
    if (left == "JobDataSize_Normal")
    {
        JobDataSize_Normal = ConvertToBool(right);
    }
    if (left == "JobDataSize_Normal_Mean")
    {
        JobDataSize_Normal_Mean = ConvertToDouble(right);
    }
    if (left == "JobDataSize_Normal_STDev")
    {
        JobDataSize_Normal_STDev = ConvertToDouble(right);
    }



  }
}

bool Configuration::ConvertToBool(std::string &data)
{
  if (data.compare("true") == 0)
    return true;
  return false;

//  std::istringstream istrs(data);
//  bool result;
//  return istrs >> result ? result : 0;
}

int Configuration::ConvertToInt(std::string &data)
{
  std::istringstream istrs(data);
  int result;
  return istrs >> result ? result : 0;
}

double Configuration::ConvertToDouble(std::string &data)
{
  std::istringstream istrs(data);
  double result;
  return istrs >> result ? result : 0;
}


void Configuration::PrintConfiguration()
{

  std::cout << "LogLevel = " << LogLevel << std::endl;
  std::cout << "PauseAtEndOfCode = " << PauseAtEndOfCode << std::endl;
  std::cout << "MaxTime = " << MaxTime << std::endl;
  std::cout << "TimeStep = " << TimeStep << std::endl;
  std::cout << "BandwidthPerMinuteForClusterInMegaBytes = " << BandwidthPerMinuteForClusterInMegaBytes << std::endl;
  std::cout << "BandwidthPerMinuteForWiredLinksInMegaBytes = " << BandwidthPerMinuteForWiredLinksInMegaBytes << std::endl;
  std::cout << "NumberOfParkingSpaces = " << NumberOfParkingSpaces << std::endl;
  std::cout << "MaxVehicleUtilization = " << MaxVehicleUtilization << std::endl;
  std::cout << "MaxJobsInInitialSetup = " << MaxJobsInInitialSetup << std::endl;
  std::cout << "NumberTasksPerJob = " << NumberTasksPerJob << std::endl;
  std::cout << "TaskScheme_AlternateProcessAndDataMigrate = " << TaskScheme_AlternateProcessAndDataMigrate << std::endl;
  std::cout << "VMMigrationOffset = " << VMMigrationOffset << std::endl;
  std::cout << "NumberOfDataBackupsRequired = " << NumberOfDataBackupsRequired << std::endl;
  std::cout << "DataMigrationType_Random = " << DataMigrationType_Random << std::endl;
  std::cout << "DataMigrationType_TwoClusterOneGroup_Random = " << DataMigrationType_TwoClusterOneGroup_Random << std::endl;
  std::cout << "CarArrival_FromFile = " << CarArrival_FromFile << std::endl;
  std::cout << "CarArrival_Static = " << CarArrival_Static << std::endl;
  std::cout << "CarArrival_Static_Value = " << CarArrival_Static_Value << std::endl;
  std::cout << "CarArrival_Poisson = " << CarArrival_Poisson << std::endl;
  std::cout << "CarArrival_Poisson_Lambda = " << CarArrival_Poisson_Lambda << std::endl;
  std::cout << "CarDeparture_Static = " << CarDeparture_Static << std::endl;
  std::cout << "CarDeparture_Static_Value = " << CarDeparture_Static_Value << std::endl;
  std::cout << "CarDeparture_Exponential = " << CarDeparture_Exponential << std::endl;
  std::cout << "CarDeparture_Exponential_Mean = " << CarDeparture_Exponential_Mean << std::endl;
  std::cout << "JobArrival_Static = " << JobArrival_Static << std::endl;
  std::cout << "JobArrival_Static_Value = " << JobArrival_Static_Value << std::endl;
  std::cout << "JobArrival_Poisson = " << JobArrival_Poisson << std::endl;
  std::cout << "JobArrival_Poisson_Lambda = " << JobArrival_Poisson_Lambda << std::endl;
  std::cout << "JobLength_Static = " << JobLength_Static << std::endl;
  std::cout << "JobLength_Static_Value = " << JobLength_Static_Value << std::endl;
  std::cout << "JobLength_Normal = " << JobLength_Normal << std::endl;
  std::cout << "JobLength_Normal_Mean = " << JobLength_Normal_Mean << std::endl;
  std::cout << "JobLength_Normal_STDev = " << JobLength_Normal_STDev << std::endl;
  std::cout << "JobVMSize_Static = " << JobVMSize_Static << std::endl;
  std::cout << "JobVMSize_Static_Value = " << JobVMSize_Static_Value << std::endl;
  std::cout << "JobVMSize_Normal = " << JobVMSize_Normal << std::endl;
  std::cout << "JobVMSize_Normal_Mean = " << JobVMSize_Normal_Mean << std::endl;
  std::cout << "JobVMSize_Normal_STDev = " << JobVMSize_Normal_STDev << std::endl;
  std::cout << "JobDataSize_Static = " << JobDataSize_Static << std::endl;
  std::cout << "JobDataSize_Static_Value = " << JobDataSize_Static_Value << std::endl;
  std::cout << "JobDataSize_Normal = " << JobDataSize_Normal << std::endl;
  std::cout << "JobDataSize_Normal_Mean = " << JobDataSize_Normal_Mean << std::endl;
  std::cout << "JobDataSize_Normal_STDev = " << JobDataSize_Normal_STDev << std::endl;

}


void Configuration::WriteConfigSettings()
{
   ResultsLogger _results;


    _results.results << MaxTime
      << "," << BandwidthPerMinuteForClusterInMegaBytes
      << "," << BandwidthPerMinuteForWiredLinksInMegaBytes
      << "," << NumberOfParkingSpaces
      << "," << MaxVehicleUtilization
      << "," << MaxJobsInInitialSetup
      << "," << NumberTasksPerJob
      << "," << TaskScheme_AlternateProcessAndDataMigrate
      << "," << VMMigrationOffset
      << "," << NumberOfDataBackupsRequired
      //<< "," << DataMigrationType_Random
      << "," << DataMigrationType_TwoClusterOneGroup_Random
      << "," << CarArrival_FromFile
      << "," << CarArrival_Static
      << "," << CarArrival_Static_Value
      << "," << CarArrival_Poisson
      << "," << CarArrival_Poisson_Lambda
      << "," << CarDeparture_Static
      << "," << CarDeparture_Static_Value
      << "," << CarDeparture_Exponential
      << "," << CarDeparture_Exponential_Mean
      << "," << JobArrival_Static
      << "," << JobArrival_Static_Value
      << "," << JobArrival_Poisson
      << "," << JobArrival_Poisson_Lambda
      << "," << JobLength_Static
      << "," << JobLength_Static_Value
      << "," << JobLength_Normal
      << "," << JobLength_Normal_Mean
      << "," << JobLength_Normal_STDev
      << "," << JobVMSize_Static
      << "," << JobVMSize_Static_Value
      << "," << JobVMSize_Normal
      << "," << JobVMSize_Normal_Mean
      << "," << JobVMSize_Normal_STDev
      << "," << JobDataSize_Static
      << "," << JobDataSize_Static_Value
      << "," << JobDataSize_Normal
      << "," << JobDataSize_Normal_Mean
      << "," << JobDataSize_Normal_STDev;

      }
