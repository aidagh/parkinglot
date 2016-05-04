//File:         JobDistributionModel.cpp
//Description:  


#include "JobDistributionModel.hpp"

int JobDistributionModel::getNextJobLength()
{
	//TODO: Obviously this needs to be adjusted
	return 20;
	
}

int JobDistributionModel::getNextArrival()
{
	if (NextArrival == 0)
	{
		generateNext();
	}	
	return NextArrival;
}
int JobDistributionModel::getNextVMSize()
{
	//TODO: Obviously this needs to be adjusted
	return 5;
	
}
double JobDistributionModel::getNextJobDataToMigrate()
{
	//TODO: Obviously this needs to be adjusted
	return 0;
	
}

int JobDistributionModel::generateNext()
{
  //TODO: This needs to be updated to work based on the configuration
  NextArrival = _time.getTime() + 5;
  
  /*
  if (_configuration.CarResidency_FromFile)
  {
	  //Use pre-existing file
  }
  else if (_configuration.CarResidency_Static)
  {
	  //CarResidency_Static_Hours;   
  }
  else if (_configuration.CarResidency_Exponential)
  {
	//_configuration.CarResidency_Exponential_Lambda;  
  }
  */
}

