//File:        JobVMSizeDistributionFactory.hpp
//Description:  A factory object that returns an implementation based on the selected distribution
//  *make_JobVMSizeDistribution - returns a pointer to a Job VM Size Distribution
//      choice:0 - Static Departure
//      choice:1 - Normal Departure


#ifndef __JOBVMSIZEDISTRIBUTIONFACTORY_HPP__
#define __JOBVMSIZEDISTRIBUTIONFACTORY_HPP__

#include "DistributionType.enum"

class JobVMSizeDistributionFactory
{
	public:
	    static JobVMSizeDistributionFactory *make_JobVMSizeDistribution(DistributionType distribution);
		virtual void Initialize() = 0;  //=0 because we have to declare some function;
		virtual int getNext() = 0;      //=0 because we have to declare some function;

		JobVMSizeDistributionFactory();
        virtual ~JobVMSizeDistributionFactory();

};

#endif
