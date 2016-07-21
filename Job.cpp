//File:         Job.cpp
//Description:

#include "Job.hpp"

Job::Job()
{
  jobStatus = Idle;
  jobProcessingTime = 0;
  jobProcessingTimeLeft = 999;
  VMMigrationJob = NULL;
}


void Job::printJobDetails(bool printChildDetails, std::string tab)
{
    Logger log;
    *log.debug << tab << "Job Assigned" << std::endl;
    *log.debug << tab << "    Job Number:     " << job_number << std::endl;
    *log.debug << tab << "    Job Status:     " << PrintJobStatus(jobStatus) << std::endl;
    *log.debug << tab << "    Car Number:     " << car->car_spot_number << std::endl;
    *log.debug << tab << "    Job Processing: " << jobProcessingTimeLeft << " of " << jobProcessingTime << " left to process" << std::endl;

    if (printChildDetails)
    {
        std::list<JobTask*>::iterator it_jobTask;

        if(!JobTasks.empty())
        {
            for(it_jobTask = JobTasks.begin(); it_jobTask != JobTasks.end(); it_jobTask++)
            {
                (*it_jobTask)->printJobTaskDetails(true, tab + "    ");
            }
        }


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
        case InitialSetup:
            return "Initial Setup";
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
