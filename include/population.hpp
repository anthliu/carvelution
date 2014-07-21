#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include <Box2d/Box2d.h>
#include "genome.hpp"

class Population
{
  /*Holds a population of Car genes
   */
  int roulette();//return index of a random car. weighted according to score
  float totalScore;//used for calculating roulette()
public:
  std::vector <Genome> car;
  std::vector <float32> score;
  Population(int populationNumber);
  Population(const Population& otherPopulation);//for copying populations in the passOn() function
  void passOn();//makes a new generation of cars based on roullete wheel with weight based on score
};

#endif
