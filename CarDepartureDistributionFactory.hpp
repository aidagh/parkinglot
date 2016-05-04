//File:         CarDepartureDistributionFactory.hpp
//Description:  


#ifndef __CARDEPARTUREDISTRIBUTIONFACTORY_HPP__
#define __CARDEPARTUREDISTRIBUTIONFACTORY_HPP__

class CarDepartureDistributionFactory
{
	public:
	    static CarDepartureDistributionFactory *make_CarDepartureDistribution(int choice);
		virtual void Initialize() = 0;  //=0 because we have to declare some function;
		virtual int getNext() = 0;      //=0 because we have to declare some function;
	
};

#endif