//File:        JobDataSizeDistributionFactory.hpp
//Description:  A factory object that returns an implementation based on the selected distribution
//  *make_JobDataSizeDistribution - returns a pointer to a Job VM Size Distribution
//      choice:0 - Static Departure
//      choice:1 - Normal Departure


#ifndef __JOBDataSizeDISTRIBUTIONFACTORY_HPP__
#define __JOBDataSizeDISTRIBUTIONFACTORY_HPP__

#include "DistributionType.enum"

class JobDataSizeDistributionFactory
{
	public:
	    static JobDataSizeDistributionFactory *make_JobDataSizeDistribution(DistributionType distribution);
		virtual void Initialize() = 0;  //=0 because we have to declare some function;
		virtual int getNext() = 0;      //=0 because we have to declare some function;
	
};

#endif