//File:         Job.cpp
//Description:

#include "Job.hpp"

Job::Job()
{
  jobStatus = Idle;
  jobSize = 0;
  jobSizeLeftToProcess = 999;
  VMMigrationJob = NULL;
}


void Job::printJobDetails(bool printChildDetails, std::string tab)
{
    Logger log;
    *log.debug << tab << "Job Assigned" << std::endl;
    *log.debug << tab << "    Job Number:     " << job_number << std::endl;
    *log.debug << tab << "    Job Status:     " << PrintJobStatus(jobStatus) << std::endl;
    *log.debug << tab << "    Car Number:     " << car->car_spot_number << std::endl;
    *log.debug << tab << "    Job Processing: " << jobSizeLeftToProcess << " of " << jobSize << " left to process" << std::endl;

    if (printChildDetails)
    {
        std::list<MigrationJob*>::iterator it;

        if(!DataMigrationJobs.empty())
        {
            for(it = DataMigrationJobs.begin(); it != DataMigrationJobs.end(); it++)
            {
                (*it)->printMigrationJobDetails(true, tab + "    ");
            }
        }
        if(VMMigrationJob != NULL)
        {
            VMMigrationJob->printMigrationJobDetails(true, tab + "    ");
        }
    }
}


std::string Job::PrintJobStatus(JobStatus jobStatus)
{
    switch (jobStatus)
    {
        case Idle:
            return "Idle";
        case Processing:
            return "Processing";
        case VMMigrating:
            return "VMMigrating";
        case VMMigrationComplete:
            return "VMMigrationComplete";
        case DataMigrating:
            return "DataMigrating";
        case Complete:
            return "Complete";
        default:
            return "Status Not Mapped";
    }
}
