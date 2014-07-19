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
