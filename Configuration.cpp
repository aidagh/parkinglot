//File:         Configuration.cpp
//Description: 	Provides configuration data to the application

#include <fstream>

#include "Configuration.hpp"

int Configuration::LogLevel = 0;
bool Configuration::PauseAtEndOfCode = true;
int Configuration::MaxTime = 100;
int Configuration::TimeStep = 1;
double Configuration::BandwidthPerSecondForCluster = .125;
int Configuration::NumberOfParkingSpaces = 10;

int Configuration::VMMigrationOffset = 10;
int Configuration::NumberOfDataBackupsRequired = 3;
bool Configuration::DataMigrationType_Random = true;

bool Configuration::CarArrival_FromFile = false;
bool Configuration::CarArrival_Static = true;
int Configuration::CarArrival_Static_Value = 5;
bool Configuration::CarArrival_Poisson = false;
double Configuration::CarArrival_Poisson_Lambda = 0.1;

bool Configuration::CarDeparture_Static = true;
int Configuration::CarDeparture_Static_Value = 25;
bool Configuration::CarDeparture_Exponential = false;
double Configuration::CarDeparture_Exponential_Lambda = 0.1;


bool Configuration::JobArrival_Static = true;
int Configuration::JobArrival_Static_Value = 10;
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


void Configuration::ReadFromFile()
{
  std::ifstream file;
  std::string line;
  file.open("config.in", std::fstream::in);
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
    if (left == "BandwidthPerSecondForCluster")
    {
      BandwidthPerSecondForCluster = ConvertToDouble(right);
    }
    if (left == "NumberOfParkingSpaces")
    {
      NumberOfParkingSpaces = ConvertToInt(right);
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
	  CarArrival_Static_Value = ConvertToInt(right);
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
	  CarDeparture_Static_Value = ConvertToInt(right);
	}
    if (left == "CarDeparture_Exponential")
	{
	  CarDeparture_Exponential = ConvertToBool(right);
	}
    if (left == "CarDeparture_Exponential_Lambda")
	{
	  CarDeparture_Exponential_Lambda = ConvertToDouble(right);
	}
/*
JobArrival_Static
JobArrival_Static_Value
JobArrival_Poisson
JobArrival_Poisson_Lambda

JobLength_Static
JobLength_Static_Value
JobLength_Normal
JobLength_Normal_Mean
JobLength_Normal_STDev

JobVMSize_Static
JobVMSize_Static_Value
JobVMSize_Normal
JobVMSize_Normal_Mean
JobVMSize_Normal_STDev
*/

  }
}

bool Configuration::ConvertToBool(std::string &data)
{
  std::istringstream istrs(data);
  bool result;
  return istrs >> result ? result : 0;
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
