//File:         Random.cpp
//Description:

#include "Random.hpp"
#include "Configuration.hpp"


 std::default_random_engine Random::generator;
 std::uniform_int_distribution<> Random::uniformDistribution;



void Random::Initialize()
{
  Configuration _configuration;
  generator = std::default_random_engine(_configuration.Seed);
  uniformDistribution = std::uniform_int_distribution<> (0, RAND_MAX);
}

int Random::GetNextInt(int max)
{
  return uniformDistribution(generator) % max;
}

double Random::GetNextDouble(double max)
{
  return ((double)uniformDistribution(generator) / (RAND_MAX)) * max;
}

