#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>

#include "../include/genome.hpp"
#include "../include/randomgen.hpp"

Genome::Genome()
{
  /*random genome initializer*/
  for (int i = 0; i < 8; i++)
    {
      legAngleWeight[i] = randAngleWeight();
      legLength[i] = randLength();
    }
  for (int i = 0; i < 2; i++)
    {
      wheelLeg[i] = randWheel();
      wheelLength[i] = randWheelLength();
    }

  color = sf::Color(randHue(), randHue(), randHue());
}

Genome::Genome(float32 setAngleWeight[8], float32 setLegLength[8], int setWheelLeg[2], float32 setWheelLength[2], sf::Color setColor)
{
  std::copy(legAngleWeight, legAngleWeight + 8, setAngleWeight);
  std::copy(legLength, legLength + 8, setLegLength);
  std::copy(wheelLeg, wheelLeg + 2, setWheelLeg);
  std::copy(wheelLength, wheelLength + 2, setWheelLength);
  color = setColor;
}

void Genome::mutateLegAngleWeight(int number)
{
  legAngleWeight[number] = randAngleWeight();
}

void Genome::mutateLegLength(int number)
{
  legLength[number] = randLength();
}

void Genome::mutateWheelLeg(int number)
{
  wheelLeg[number] = randWheel();
}

void Genome::mutateWheelLength(int number)
{
  wheelLength[number] = randWheelLength();
}

void Genome::mutateColor()
{
  color = sf::Color(randHue(), randHue(), randHue());
}

void Genome::mutate(float32 mutateRate)
{
  /*mutateRate : 0.0f to 1.0f*/
  for (int i = 0; i < 8; i++)
    {
      if (randFloat(0.0f, 1.0f) <= mutateRate)
	legAngleWeight[i] = randAngleWeight();
      if (randFloat(0.0f, 1.0f) <= mutateRate)
	legLength[i] = randLength();
    }
  for (int i = 0; i < 2; i++)
    {
      if (randFloat(0.0f, 1.0f) <= mutateRate)
	wheelLeg[i] = randWheel();
      if (randFloat(0.0f, 1.0f) <= mutateRate)
	wheelLength[i] = randWheelLength();
    }

  if (randFloat(0.0f, 1.0f) <= mutateRate)
    color = sf::Color(randHue(), randHue(), randHue());
}
