#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <cmath>
#include <random>
#include <algorithm>

#include "car.hpp"

float32 randAngleWeight()
{
  /*Retrieves a random weight from 0.02 to 1.0

    todo- set minimum weight constant*/
  std::uniform_real_distribution<float32> angle(0.02f, 1.0f);
  return angle;
}

float32 randLength()
{
  /*Retrieves a random length for either a "leg" or a wheel

    todo - set max length constant
    - set max wheel ratio*/

  std::uniform_real_distribution<float32> length(0.0f, 10.0f);
  return length;
}

int randWheel()
{
  /*rand number from 0 to 7*/
  std::uniform_real_distribution<int> number(0, 8);
  return number;
}

Car::Car(b2World* setWorld)
{
  /*The random initializer for a car. */
  world = setWorld
  for (int i = 0; i < 8; i++)
    {
      legAngle[i] = randAngleWeight();
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
  legAngleWeight = setAngleWeight;
  legLength = setLegLength;
  wheel = setWheel;
  world = setWorld;
  
  buildBody();
}

Car::buildBody()
{
  /* the center of the car is the origin; (0.0, 0.0)
   
   todo - set fixture constants such as friction, density etc.*/

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 4.0f);
  body = world.CreateBody(&bodyDef);

  // - make the polygon shape
  b2Vec2 vertices[8];
  float32 totalAngleWeight = 0;
  float32 angle = 0;
  for (int i = 0; i < 8; i++)//find totalAngleWeight
    {
      totalAngleWeight += legAngleWeight[0];
    }

  vertices[0].Set(legLength[0], 0.0f);//first vertice is always on the x axis
  for (int i = 1; i < 8; i++)//set vertices; note: legAngleWeight[7] is not used because it determines the angle of vertice[0], and since verice[0] is always on the x axis, it only influences the totalAngleWeight
    {
      angle += 2 * M_PI * legAngleWeight[i - 1] / totalAngleWeight;
      vertices[i].Set(legLength[i] * cos(angle), legLength[i] * sin(angle));
    }

  
  b2PolygonShape polygon;
  polygon.Set(vertices, count);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &polygon;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  fixtureDef.restitution = 0.0f;

  body->CreateFixture(&fixtureDef);
}
