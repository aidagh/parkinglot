
#include "MigrationJob.hpp"

void MigrationJob::printMigrationJobDetails(bool printChildDetails, std::string tab)
{
    *log.info << tab << "Migration Task" << std::endl;


    *log.info << tab << "    type:  " << PrintMigrationType(type) << ", from Car(" << carFrom->car_spot_number << ") to Car (" << carTo->car_spot_number << ")." << std::endl;
    *log.info << tab << "    Data left to Migrate " << dataLeftToMigrate << " of " << totalDataSize << std::endl;
    *log.info << tab << "    currentBandwidth     " << currentBandwidthSize << std::endl;
}

std::string MigrationJob::PrintMigrationType(MigrationType type)
{
    switch (type)
    {
        case VM:
            return "VM";
        case Data:
            return "Data";
        default:
            return "Type Not Mapped";
    }

}
