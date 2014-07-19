#include <stdio.h>
#include <Box2d/Box2d.h>
#include "../include/randomgen.hpp"
#include "../include/configurations.hpp"

float32 randAngleWeight()
{
  /*Retrieves a random weight from 0.02 to 1.0
   */
  return conf::minAngleWeight + (static_cast <float32> (rand()) / static_cast <float32> (RAND_MAX / (1.0 - conf::minAngleWeight)));
}

float32 randLength()
{
  /*Retrieves a random length for either a "leg" or a wheel

    */

  return (static_cast <float32> (rand()) / static_cast <float32> (RAND_MAX / conf::maxLength));
}

float32 randWheelLength()
{
  return randLength() / 2.0f;
}

int randWheel()
{
  /*rand number from 0 to 7*/
  return rand() % 8;
}

int randHue()
{
  return (rand() % 192);
}

void extendBaseHilly(std::vector <b2Vec2>& setPoint)
{
  for (int i = 0; i < conf::extendNumber; i++)
    {
      float32 yChange = conf::baseHillyChange - (static_cast <float32> (rand()) / static_cast <float32> (RAND_MAX / (conf::baseHillyChange * 2)));
      setPoint.push_back(b2Vec2(setPoint.back().x + conf::extendUnitLength, setPoint[0].y + yChange));
    }
}
