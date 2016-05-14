
#ifndef __MIGRATIONJOB_HPP__
#define __MIGRATIONJOB_HPP__

#include "Logger.hpp"
#include "Job.hpp"
#include "Car.hpp"

class Car;
class Job;

enum MigrationType
{
	Data,
	VM

};


class MigrationJob
{
    Logger log;

	public:
      Job * jobFrom;
	  Car * carFrom;
	  Car * carTo;
	  MigrationType type;

	  double totalDataSize;
	  double dataLeftToMigrate;

	  double currentBandwidthSize;

	  void printMigrationJobDetails(bool printChildDetails, std::string tab);
	  std::string PrintMigrationType(MigrationType type);
};


#endif
