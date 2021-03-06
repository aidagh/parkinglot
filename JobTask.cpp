//File:         JobTask.cpp
//Description:

#include "JobTask.hpp"

JobTask::JobTask()
{
  jobTaskStatus = Task_NotStarted;
  taskProcessingTime = 0;
  taskProcessingTimeLeft = 999;
}


void JobTask::printJobTaskDetails(bool printChildDetails, std::string tab)
{
    Logger log;
    *log.debug << tab << "Job Task" << std::endl;
//    *log.debug << tab << "    Job Number:     " << job_number << std::endl;
    *log.debug << tab << "    Job Task Status:     " << PrintJobTaskStatus(jobTaskStatus) << std::endl;
    *log.debug << tab << "    Job Type:     " << PrintJobTaskType(taskType) << std::endl;
    if (taskType == Task_Process)
    {
      *log.debug << tab << "      Job Task Processing: " << taskProcessingTimeLeft << " of " << taskProcessingTime << " left to process" << std::endl;
    }
    if (taskType == Task_DataMigrate)
    {
      *log.debug << tab << "      Job Task Data To Migrate: " << taskDataToMigrate << std::endl;
    }

//    if (printChildDetails)
//    {
//        std::list<MigrationJob*>::iterator it;
//
//        if(!DataMigrationJobs.empty())
//        {
//            for(it = DataMigrationJobs.begin(); it != DataMigrationJobs.end(); it++)
//            {
//                (*it)->printMigrationJobDetails(true, tab + "    ");
//            }
//        }
//        if(VMMigrationJob != NULL)
//        {
//            VMMigrationJob->printMigrationJobDetails(true, tab + "    ");
//        }
//    }
}


std::string JobTask::PrintJobTaskStatus(JobTaskStatus jobTaskStatus)
{
    switch (jobTaskStatus)
    {
        case Task_NotStarted:
            return "Not Started";
        case Task_InProgress:
            return "In Progress";
        case Task_Complete:
            return "Complete";
        default:
            return "Status Not Mapped";
    }
}

std::string JobTask::PrintJobTaskType(JobTaskType jobTaskType)
{
    switch (jobTaskType)
    {
        case Task_Process:
            return "Process";
        case Task_DataMigrate:
            return "Data Migrate";
        default:
            return "Type Not Mapped";
    }
}
