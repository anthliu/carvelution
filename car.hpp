#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>

float32 randAngle();
float32 randLength();

class Car
{
  float32 legAngle[8];
  float32 legLength[8];
  float32 wheel[8];
  b2Body* body;
public:
  Car(b2World world);
  draw(sf::RenderWindow& window);
}

#endif
