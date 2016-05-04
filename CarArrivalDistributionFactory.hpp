//File:         CarArrivalDistributionFactory
//Description: 
//
//
//


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