
#ifndef __MIGRATIONJOB_HPP__
#define __MIGRATIONJOB_HPP__

#include "Car.hpp"

class Car;

enum MigrationType
{
	Data,
	VM
	
};


class MigrationJob
{
	public:
	  Car * carFrom;
	  Car * carTo;
	  MigrationType type;
	  double dataLeftToMigrate;
	  double currentBandwidthSize;
};

#endif