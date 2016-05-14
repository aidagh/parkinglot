//File:         Random.cpp
//Description:

#include "Random.hpp"

void Random::Initialize()
{
  mersenneTwisterEngine = std::mt19937(device());
  uniformDistribution = std::uniform_int_distribution<> (0, RAND_MAX);
}

int Random::GetNextInt(int max)
{
  return uniformDistribution(mersenneTwisterEngine) % max;
}

double Random::GetNextDouble(double max)
{
  return ((double)uniformDistribution(mersenneTwisterEngine) / (RAND_MAX)) * max;
}

