//File:         JobLengthDistributionFactory.hpp
//Description:  A factory object that returns an implementation based on the selected distribution
//  *make_JobLegthDistribution - returns a pointer to a Departure Distribution
//      choice:0 - Static Departure
//      choice:1 - Normal Departure


#ifndef __JOBLENGTHDISTRIBUTIONFACTORY_HPP__
#define __JOBLENGTHDISTRIBUTIONFACTORY_HPP__

class JobLengthDistributionFactory
{
	public:
	    static JobLengthDistributionFactory *make_JobLengthDistribution(int choice);
		virtual void Initialize() = 0;  //=0 because we have to declare some function;
		virtual int getNext() = 0;      //=0 because we have to declare some function;
	
};

#endif