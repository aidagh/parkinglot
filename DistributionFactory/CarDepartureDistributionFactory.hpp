//File:         CarDepartureDistributionFactory.hpp
//Description:  A factory object that returns an implementation based on the selected distribution
//  *make_CarDepartureDistribution - returns a pointer to a Departure Distribution
//      choice:0 - Static Departure
//      choice:1 - Exponential Departure


#ifndef __CARDEPARTUREDISTRIBUTIONFACTORY_HPP__
#define __CARDEPARTUREDISTRIBUTIONFACTORY_HPP__

#include "DistributionType.enum"

class CarDepartureDistributionFactory
{
	public:
	    static CarDepartureDistributionFactory *make_CarDepartureDistribution(DistributionType distribution);
		virtual void Initialize() = 0;  //=0 because we have to declare some function;
		virtual int getNext() = 0;      //=0 because we have to declare some function;
	
};

#endif