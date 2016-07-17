// basic file operations
#include <iostream>
#include <fstream>
#include <sstream>

//using namespace std;

std::string ConvertToString(int i)
{
  std::stringstream ss;
  ss << i;
  return ss.str();

}
std::string ConvertToString(double d)
{
  std::stringstream ss;
  ss << d;
  return ss.str();
}


int main () {
  std::ofstream configfile;
  std::ofstream batch;


  batch.open("run.bat", std::ofstream::out | std::ofstream::app);


  int bandwidthArr [] = {56, 75, 100};
  double jobarrivalArr [] = {.1, 1, 5, 10};
  int joblengthArr [] = {60, 120, 180, 240, 300};


  int bandwidth;
  double jobarrival;
  int joblength;
  for (int bandwidthLoop=0; bandwidthLoop < sizeof(bandwidthArr) / sizeof(bandwidthArr[0]); bandwidthLoop++)
  {
      for (int jobarrivalLoop=0; jobarrivalLoop < sizeof(jobarrivalArr) / sizeof(jobarrivalArr[0]); jobarrivalLoop++)
      {
          for (int joblengthLoop=0; joblengthLoop < sizeof(joblengthArr) / sizeof(joblengthArr[0]); joblengthLoop++)
          {
              bandwidth = bandwidthArr[bandwidthLoop] * 7.5;
              jobarrival = jobarrivalArr[jobarrivalLoop];
              joblength = joblengthArr[joblengthLoop];

              std::string bandwidthStr = ConvertToString(bandwidth);
              std::string jobarrivalStr = ConvertToString(jobarrival);
              std::string joblengthStr = ConvertToString(joblength);

                   std::string file = "c_" + bandwidthStr + "_" + jobarrivalStr + "_" + joblengthStr + ".config";

                   batch << "bin\\debug\\ParkingLot.exe ConfigBuilder\\" + file << std::endl;

      configfile.open ( file.c_str());
      configfile << "";
        configfile << "LogLevel=3" << std::endl;
        configfile << "PauseAtEndOfCode=false" << std::endl;
        configfile << "MaxTime=10080" << std::endl;
        configfile << "TimeStep=1" << std::endl;
        configfile << "BandwidthPerMinuteForClusterInMegaBytes=" << bandwidthStr << std::endl;
        configfile << "BandwidthPerMinuteForWiredLinksInMegaBytes=7500" << std::endl;
        configfile << "NumberOfParkingSpaces=2560" << std::endl;
        configfile << "NumberTasksPerJob=4" << std::endl;
        configfile << "TaskScheme_AlternateProcessAndDataMigrate=true" << std::endl;
        configfile << "VMMigrationOffset=60" << std::endl;
        configfile << "NumberOfDataBackupsRequired=3" << std::endl;
        configfile << "DataMigrationType_Random=true" << std::endl;
        configfile << "CarArrival_FromFile=false" << std::endl;
        configfile << "CarArrival_Static=true" << std::endl;
        configfile << "CarArrival_Static_Value=5" << std::endl;
        configfile << "CarArrival_Poisson=false" << std::endl;
        configfile << "CarArrival_Poisson_Lambda=0.1" << std::endl;
        configfile << "CarDeparture_Static=false" << std::endl;
        configfile << "CarDeparture_Static_Value=25" << std::endl;
        configfile << "CarDeparture_Exponential=true" << std::endl;
        configfile << "CarDeparture_Exponential_Mean=480" << std::endl;
        configfile << "JobArrival_Static=false" << std::endl;
        configfile << "JobArrival_Static_Value=10" << std::endl;
        configfile << "JobArrival_Poisson=true" << std::endl;
        configfile << "JobArrival_Poisson_Lambda=" << jobarrivalStr << std::endl;
        configfile << "JobLength_Static=true" << std::endl;
        configfile << "JobLength_Static_Value=" << joblengthStr << std::endl;
        configfile << "JobLength_Normal=false" << std::endl;
        configfile << "JobLength_Normal_Mean=240" << std::endl;
        configfile << "JobLength_Normal_STDev=60" << std::endl;
        configfile << "JobVMSize_Static=true" << std::endl;
        configfile << "JobVMSize_Static_Value=500" << std::endl;
        configfile << "JobVMSize_Normal=false" << std::endl;
        configfile << "JobVMSize_Normal_Mean=10" << std::endl;
        configfile << "JobVMSize_Normal_STDev=3" << std::endl;
        configfile << "JobDataSize_Static=true" << std::endl;
        configfile << "JobDataSize_Static_Value=2000" << std::endl;
        configfile << "JobDataSize_Normal=false" << std::endl;
        configfile << "JobDataSize_Normal_Mean=2000" << std::endl;
        configfile << "JobDataSize_Normal_STDev=500" << std::endl;



      configfile.close();


          }
      }
  }

batch.close();
  return 0;
}
