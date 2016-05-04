//File:         Random.hpp
//Description:  

#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__


//Class will be updated to handle a seed so that many runs can be performed with a different seed.
class Random
{
	
  public:

  int GetNextInt(int max);
  double GetNextDouble(double max);
  

};

int Random::GetNextInt(int max)
{
  return rand() % max;
}

double Random::GetNextDouble(double max)
{
  return ((double)rand() / (RAND_MAX)) * max;
}

#endif