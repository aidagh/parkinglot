//File:         Job.cpp
//Description:

#include "Job.hpp"


Job::Job()
{
//  job_flag_start_migration = false;
//  job_flag_end_migration = false;
//  data_replication_time_to_same_cluster=0;
//  data_replication_time_to_same_region=0;
//  data1_car_number = -1;
//  data2_car_number = -1;

  jobStatus = Idle;

  jobSize = 0;
  jobSizeLeftToProcess = 999;

  VMMigrationJob = NULL;
//  std::list<MigrationJob> ActiveMigrationJobs;
//  std::list<int> DataMigrationSet;

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


//
////This displays the job information which is assigned to all the cars in the parking lot as soon as simulation starts.
//void Job::display_job_information(std::ofstream& outFile)
//{
//  outFile<<"\n";
//  outFile<<"-----------------------------------------"<<"\n";
//  outFile<<"		Job Details		        "<<"\n";
//  outFile<<"-----------------------------------------"<<"\n";
//  outFile<<"job number : "<<job_number<<"\n";
//  outFile<<"job size : "<<VM_size<<"\n";
//  outFile<<"car number that this job is assigned to : "<<car_number<<"\n";
//}
//

/*
void Job::calculate_VM_size(){
  // our jobs are between 1 GB and 5 GB
  VM_size= rand()%(5000-1000)+1000;
  VM_migration_remained = VM_size;
}


// Calculates the time it takes to complete a job in a car.
void Job::calculate_job_duration(){
  //we assume that 1 MB takes 1/10 minute to finish
  job_duration= (VM_size*0.1);
  job_duration_remained = job_duration;
}
*/
