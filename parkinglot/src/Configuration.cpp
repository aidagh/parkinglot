//File:         Configuration.cpp
//Description: 	Provides configuration data to the application


#include "Configuration.hpp"

Configuration::Configuration()
{
    //ctor
}

Configuration::~Configuration()
{
    //dtor
}

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

