//File:         CarArrivalDistributionFactory.hpp
//Description:  A factory object that returns an implementation based on the selected distribution 
//  *make_CarArrivalDistribution - returns a pointer to a Arrival Distribution
//      choice:0 - Static Arrival
//      choice:1 - Poisson Arrival


#ifndef __CARARRIVALDISTRIBUTIONFACTORY_HPP__
#define __CARARRIVALDISTRIBUTIONFACTORY_HPP__

class CarArrivalDistributionFactory
{
	public:
	    static CarArrivalDistributionFactory *make_CarArrivalDistribution(int choice);
		virtual void Initialize() = 0;  //=0 because we have to declare some function;
		virtual int getNext() = 0;      //=0 because we have to declare some function;
	
};

#endif