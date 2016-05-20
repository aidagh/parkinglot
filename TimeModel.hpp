//File:         TimeModel.hpp
//Description:

#ifndef TIMEMODEL_HPP
#define TIMEMODEL_HPP

class TimeModel
{
  private:
    static int time;

  public:
    void initialize();
	void increment();
	int getTime();
};

#endif
