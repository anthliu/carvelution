#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>

float32 randAngleWeight();
float32 randLength();
int randWheel();
int randHue();//random hue for random color generation

class Car
{
  /*The generic genetic car class*/
  float32 legAngleWeight[8];//Weights are between 0.02 and 1.0, they determine how angle much a "leg" covers relative to other angles
  float32 legLength[8];
  float32 wheel[2][2];
  sf::Color color;
  b2Body* body;
  b2World* world;
  sf::ConvexShape drawPolygon;

  void buildBody();//build the body in b2World
public:
  Car(b2World* setWorld);//initialize random Car
  Car(float32 setAngleWeight[8], float32 setLegLength[8], float32 setWheel[2][2], sf::Color setColor, b2World* setWorld);
  ~Car();
  void draw(sf::RenderWindow& window);
};

#endif
