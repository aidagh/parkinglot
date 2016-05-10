#include "TimeModel.hpp"

int TimeModel::time = 0;

void TimeModel::initialize()
{
	time = 0;
}

void TimeModel::increment()
{
	time++;
}

int TimeModel::getTime()
{
	return time;
}
