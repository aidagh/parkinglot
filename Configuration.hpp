class Configuration
{
  public:
   static int MaxTime;
   static double BandwidthPerSecondForCluster;
   static int NumberOfParkingSpaces;
   
   static bool CarResidency_FromFile;
   static bool CarResidency_Static;
   static int CarResidency_Static_Hours;   
   static bool CarResidency_Exponential;
   static double CarResidency_Exponential_Lambda;
   
   void ReadFromFile();
   bool ConvertToBool(std::string &data);   
   int ConvertToInt(std::string &data);
   double ConvertToDouble(std::string &data);

};


int Configuration::MaxTime = 1440; 
double Configuration::BandwidthPerSecondForCluster = .125; 
int Configuration::NumberOfParkingSpaces = 10;
bool Configuration::CarResidency_FromFile = false;
bool Configuration::CarResidency_Static = true;
int Configuration::CarResidency_Static_Hours = 24;
bool Configuration::CarResidency_Exponential = false;
double Configuration::CarResidency_Exponential_Lambda = 0;