//File:         JobDistributionModel.cpp
//Description:


#include "JobDistributionModel.hpp"

int JobDistributionModel::NextArrival = 0;
int JobDistributionModel::NextJobLength = 0;
int JobDistributionModel::NextVMSize = 0;

JobArrivalDistributionFactory* JobDistributionModel::JobArrivalDistribution = NULL;
JobLengthDistributionFactory* JobDistributionModel::JobLengthDistribution = NULL;
JobVMSizeDistributionFactory* JobDistributionModel::JobVMSizeDistribution = NULL;

void JobDistributionModel::Initialize()
{
  *_log.trace << "Initializing JobDistributionModel - Job Arrival" << std::endl;

  if (_configuration.JobArrival_Static)
  {
      JobArrivalDistribution = JobArrivalDistributionFactory::make_JobArrivalDistribution(Static);
	  JobArrivalDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.JobArrival_Poisson)
  {
    JobArrivalDistribution = JobArrivalDistributionFactory::make_JobArrivalDistribution(Poisson);
	JobArrivalDistribution->Initialize();
    *_log.trace << "   Poisson" << std::endl;
  }



  *_log.trace << "Initializing JobDistributionModel - Job Length" << std::endl;

  if (_configuration.JobLength_Static)
  {
      JobLengthDistribution = JobLengthDistributionFactory::make_JobLengthDistribution(Static);
	  JobLengthDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.JobLength_Normal)
  {
    JobLengthDistribution = JobLengthDistributionFactory::make_JobLengthDistribution(Normal);
	JobLengthDistribution->Initialize();
    *_log.trace << "   Normal" << std::endl;
  }


  *_log.trace << "Initializing JobDistributionModel - VM Size" << std::endl;

  if (_configuration.JobVMSize_Static)
  {
      JobVMSizeDistribution = JobVMSizeDistributionFactory::make_JobVMSizeDistribution(Static);
	  JobVMSizeDistribution->Initialize();

	  *_log.trace << "   Static" << std::endl;
  }
  else if (_configuration.JobVMSize_Normal)
  {
    JobVMSizeDistribution = JobVMSizeDistributionFactory::make_JobVMSizeDistribution(Normal);
	JobVMSizeDistribution->Initialize();
    *_log.trace << "   Normal" << std::endl;
  }


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
	if (NextVMSize == 0)
	{
		generateNext();
	}
	return NextVMSize;
}
int JobDistributionModel::getNextJobLength()
{
	if (NextArrival == 0)
	{
		generateNext();
	}
	return NextJobLength;
}
double JobDistributionModel::getNextJobDataToMigrate()
{
	return 0;
}



int JobDistributionModel::generateNext()
{
  *_log.trace << "JobDistributionModel.generateNext()" << std::endl;

  NextArrival = _time.getTime() + JobArrivalDistribution->getNext();
  NextJobLength = JobLengthDistribution->getNext();
  NextVMSize = JobVMSizeDistribution->getNext();
}

