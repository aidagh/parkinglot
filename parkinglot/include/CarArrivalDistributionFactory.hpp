//File:         CarArrivalDistributionFactory.hpp
//Description:  A factory object that returns an implementation based on the selected distribution
//  *make_CarArrivalDistribution - returns a pointer to a Arrival Distribution
//      choice:0 - Static Arrival
//      choice:1 - Poisson Arrival


#ifndef __CARARRIVALDISTRIBUTIONFACTORY_HPP__
#define __CARARRIVALDISTRIBUTIONFACTORY_HPP__

#include "DistributionType.enum"
#include <random>
#include "Configuration.hpp"

using namespace std;

class CarArrivalDistributionFactory
{
	public:
	    static CarArrivalDistributionFactory *make_CarArrivalDistribution(DistributionType distribution);
		virtual void Initialize() = 0;  //=0 because we have to declare some function;
		virtual int getNext() = 0;      //=0 because we have to declare some function;

		CarArrivalDistributionFactory();
        virtual ~CarArrivalDistributionFactory();

};

#endif
