#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <cmath>
#include <random>
#include <algorithm>

#include "car.hpp"

float32 randAngle()
{
  std::uniform_real_distribution<float32> angle(0.0f, 2 * M_PI);
  return angle;
}

float32 randLength()
{
  std::uniform_real_distribution<float32> length(0.0f, 10.0f);
  return length
}

Car::Car(b2World world)
{
  for (int i = 0; i < 8; i++)
    {
      legAngle[i] = randAngle();
      legLength[i] = randLength();
    }
}
