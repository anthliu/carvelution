#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <stdio.h>
#include <cmath>
#include <random>
#include <algorithm>
#include "car.hpp"
#include "configurations.hpp"

float32 randAngleWeight()
{
  /*Retrieves a random weight from 0.02 to 1.0
   */
  return conf::minAngleWeight + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (1.0 - conf::minAngleWeight)));
}

float32 randLength()
{
  /*Retrieves a random length for either a "leg" or a wheel

    todo - set max wheel ratio*/

  return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX / conf::maxLength));
}

int randWheel()
{
  /*rand number from 0 to 7*/
  return rand() % 8;
}

Car::Car(b2World* setWorld)
{
  /*The random initializer for a car. */
  world = setWorld;
  for (int i = 0; i < 8; i++)
    {
      legAngleWeight[i] = randAngleWeight();
      legLength[i] = randLength();
    }
  for (int i = 0; i < 2; i++)
    {
      wheel[i][0] = randWheel();
      wheel[i][1] = randLength();
    }

  buildBody();
}

Car::Car(float32 setAngleWeight[8], float32 setLegLength[8], float32 setWheel[2][2], b2World* setWorld)
{
  std::copy(legAngleWeight, legAngleWeight + 8, setAngleWeight);
  std::copy(legLength, legLength + 8, setLegLength);
  std::copy(&wheel[0][0], &wheel[0][0] + 4, &setWheel[0][0]);
  world = setWorld;
  
  buildBody();
}

void Car::buildBody()
{
  /* the center of the car is the origin; (0.0, 0.0)
   
   todo - set fixture constants such as friction, density etc.*/

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 4.0f);
  body = world->CreateBody(&bodyDef);

  // - make the polygon shape for box2d and SFML
  drawPolygon.setPointCount(8);
  b2Vec2 vertices[8];
  float32 totalAngleWeight = 0;
  float32 angle = 0;
  for (int i = 0; i < 8; i++)//find totalAngleWeight
    {
      totalAngleWeight += legAngleWeight[0];
    }

  drawPolygon.setPoint(0, sf::Vector2f(legLength[0], 0.0f));
  vertices[0].Set(legLength[0], 0.0f);//first vertice is always on the x axis
  for (int i = 1; i < 8; i++)//set vertices; note: legAngleWeight[7] is not used because it determines the angle of vertice[0], and since verice[0] is always on the x axis, it only influences the totalAngleWeight
    {
      angle += 2 * M_PI * legAngleWeight[i - 1] / totalAngleWeight;
      vertices[i].Set(legLength[i] * cos(angle), legLength[i] * sin(angle));
      drawPolygon.setPoint(i, sf::Vector2f(conf::drawScale * legLength[i] * cos(angle), conf::drawScale * legLength[i] * sin(angle)));
    }
  
  b2PolygonShape polygon;
  polygon.Set(vertices, 8);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &polygon;
  fixtureDef.density = conf::carDensity;
  fixtureDef.friction = conf::carFriction;
  fixtureDef.restitution = conf::carRestitution;

  body->CreateFixture(&fixtureDef);
}

void Car::draw(sf::RenderWindow& window)
{
  //first get the new position of the polygon then draw
  b2Vec2 polygonPosition = body->GetPosition();
  drawPolygon.setPosition(sf::Vector2f(polygonPosition.x, -1 * polygonPosition.y));
  drawPolygon.setRotation(body->GetAngle());

  window.draw(drawPolygon);
}
