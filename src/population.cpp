#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <stdio.h>
#include "../include/genome.hpp"
#include "../include/population.hpp"
#include "../include/randomgen.hpp"
#include "../include/configurations.hpp"

Population::Population(int populationNumber) : car(populationNumber, Genome()), score(populationNumber, 0)
{
  for (std::vector<float32>::size_type i = 0; i != score.size(); i++)
    {
      totalScore += score[i];
    }
}

Population::Population(const Population& otherPopulation)
{
  car = otherPopulation.car;
  score = otherPopulation.score;
}

int Population::roulette()
{
  float32 roll = randFloat(0.0, totalScore);
  float32 temp = 0;
  for (std::vector<float32>::size_type j = 0; j != score.size(); j++)
    {
      temp += score[j];
      if (roll <= temp)
	{
	  return j;
	}
    }
  printf("roulette() is not supposed to be here...\n");
  fflush(stdout);
  return 0;
}

void Population::passOn()
{
  /*implement roulette wheel inheritance*/
  std::vector<Genome> oldCar = car;

  for (std::vector<Genome>::size_type i = 0; i != car.size(); i++)
    {
      for (int j = 0; j < 8; j++)
	{
	  car[i].legAngleWeight[j] = oldCar[roulette()].legAngleWeight[j];
	  car[i].legLength[j] = oldCar[roulette()].legLength[j];
	}
      for (int j = 0; j < 2; j++)
	{
	  car[i].wheelLeg[j] = oldCar[roulette()].wheelLeg[j];
	  car[i].wheelLength[j] = oldCar[roulette()].wheelLength[j];
	}
      car[i].color = oldCar[roulette()].color;

      car[i].mutate(conf::mutationRate);
    }
  score = std::vector<float32>(car.size(), 0.0f);
}
