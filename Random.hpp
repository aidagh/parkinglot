//File:         Random.hpp
//Description:

#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

//#include <cstdlib>
#include <random>

//Class will be updated to handle a seed so that many runs can be performed with a different seed.
class Random
{
  private:
    std::mt19937 mersenneTwisterEngine; //gen(rd());
    std::uniform_int_distribution<> uniformDistribution; //dis(1, 6);

  public:
    void Initialize();
    int GetNextInt(int max);
    double GetNextDouble(double max);

};

#endif
