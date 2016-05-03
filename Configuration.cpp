
#include "Configuration.hpp"

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
    if (left == "CarResidency_FromFile") 
	{
	  CarResidency_FromFile = ConvertToBool(right);
	}
    if (left == "CarResidency_Static") 
	{
	  CarResidency_Static = ConvertToBool(right);
	}
    if (left == "CarResidency_Static_Hours")   
	{
	  CarResidency_Static_Hours = ConvertToInt(right);
	}
    if (left == "CarResidency_Exponential") 
	{
	  CarResidency_Exponential = ConvertToBool(right);
	}
    if (left == "CarResidency_Exponential_Lambda") 
	{
	  CarResidency_Exponential_Lambda = ConvertToDouble(right);
	}
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
