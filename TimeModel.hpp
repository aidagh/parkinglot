//File:         TimeModel.hpp
//Description:  

#ifndef __TIMEMODEL_HPP__
#define __TIMEMODEL_HPP__


class TimeModel
{
  private:
    static int time;
  
  public:
    void initialize();
	void increment();
	int getTime();
	
};
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

#endif