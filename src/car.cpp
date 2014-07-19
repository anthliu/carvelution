#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include "../include/car.hpp"
#include "../include/randomgen.hpp"
#include "../include/configurations.hpp"

Car::Car(b2World* setWorld)
{
  world = setWorld;
  reset();
}

void Car::reset()
{
  /*The random initializer for a car. */
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

  buildBody();
}

Car::Car(float32 setAngleWeight[8], float32 setLegLength[8], int setWheelLeg[2], float32 setWheelLength[2], sf::Color setColor, b2World* setWorld)
{
  world = setWorld;

  reset(setAngleWeight, setLegLength, setWheelLeg, setWheelLength, setColor);
}

void Car::reset(float32 setAngleWeight[8], float32 setLegLength[8], int setWheelLeg[2], float32 setWheelLength[2], sf::Color setColor)
{
  std::copy(legAngleWeight, legAngleWeight + 8, setAngleWeight);
  std::copy(legLength, legLength + 8, setLegLength);
  std::copy(wheelLeg, wheelLeg + 2, setWheelLeg);
  std::copy(wheelLength, wheelLength + 2, setWheelLength);
  color = setColor;

  buildBody();
}

void Car::buildBody()
{
  /* the center of the car is the origin; (0.0, 0.0)
   
   */

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 0.0f);
  body = world->CreateBody(&bodyDef);

  // - make the polygon shape for box2d and SFML, and make the wheels in box2d
  drawPolygon.setPointCount(8);
  b2Vec2 vertices[8];
  float32 totalAngleWeight = 0;
  float32 angle[8] = {0};
  for (int i = 0; i < 8; i++)//find totalAngleWeight
    {
      totalAngleWeight += legAngleWeight[i];
    }
  for (int i = 1; i < 8; i++)//set angles; angle[0] is 0
    {
      angle[i] = angle[i - 1] + 2 * M_PI * legAngleWeight[i - 1] / totalAngleWeight;
    }
  for (int i = 0; i < 8; i++)//set vertices; note: legAngleWeight[7] is not used because it determines the angle of vertice[0], and since verice[0] is always on the x axis, it only influences the totalAngleWeight
    {
      vertices[i].Set(legLength[i] * cos(angle[i]), legLength[i] * sin(angle[i]));
      drawPolygon.setPoint(i, sf::Vector2f(conf::drawScale * legLength[i] * cos(angle[i]), -1 * conf::drawScale * legLength[i] * sin(angle[i])));
    }

  //box2d stuff for polygon
  b2PolygonShape polygon;
  polygon.Set(vertices, 8);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &polygon;
  fixtureDef.density = conf::carDensity;
  fixtureDef.friction = conf::carFriction;
  fixtureDef.restitution = conf::carRestitution;

  body->CreateFixture(&fixtureDef);

  //SFML polygon stuff
  sf::Color tempColor = color;
  tempColor.a = 200;
  drawPolygon.setFillColor(tempColor);
  drawPolygon.setOutlineThickness(conf::drawBorder);
  tempColor.a = 255;
  drawPolygon.setOutlineColor(tempColor);

  //Align the SFML polygon rotating origin with the Box2d center of mass
  b2Vec2 centerOfMass = body->GetWorldCenter();
  drawPolygon.setOrigin(sf::Vector2f(centerOfMass.x, centerOfMass.y));

  //Make wheels
  b2BodyDef wheelBodyDef[2];
  b2Vec2 wheelPosition[2];
  b2CircleShape wheelShape[2];
  b2FixtureDef wheelFixtureDef[2];
  b2RevoluteJointDef axisDef[2];
  for (int i = 0; i < 2; i++)
    {
      //box2d wheel stuff
      wheelBodyDef[i].type = b2_dynamicBody;
      wheelBody[i] = world->CreateBody(&wheelBodyDef[i]);

      wheelPosition[i] = b2Vec2(vertices[wheelLeg[i]].x * conf::wheelLocationRatio, vertices[wheelLeg[i]].y * conf::wheelLocationRatio);
      wheelShape[i].m_p = wheelPosition[i];
      wheelShape[i].m_radius = wheelLength[i];

      wheelFixtureDef[i].shape = &wheelShape[i];
      wheelFixtureDef[i].density = conf::wheelDensity;
      wheelFixtureDef[i].friction = conf::wheelFriction;
      wheelFixtureDef[i].restitution = conf::wheelRestitution;

      wheelBody[i]->CreateFixture(&wheelFixtureDef[i]);

      axisDef[i].Initialize(body, wheelBody[i], wheelPosition[i]);
      axisDef[i].motorSpeed = conf::axisSpeed;
      axisDef[i].maxMotorTorque = conf::maxTorque;
      axisDef[i].enableMotor = true;
      axis[i] = (b2RevoluteJoint*)world->CreateJoint(&axisDef[i]);
      //SFML draw stuff
      drawWheel[i].setRadius(conf::drawScale * wheelLength[i]);
      //drawWheel position is set when it is drawn
      tempColor = sf::Color::Black;
      tempColor.a = 200;
      drawWheel[i].setFillColor(tempColor);
      drawWheel[i].setOutlineThickness(conf::drawBorder);
      tempColor.a = 255;
      drawWheel[i].setOutlineColor(tempColor);
    }

}

void Car::draw(sf::RenderWindow& window)
{
  //first get the new position of the polygon then draw
  b2Vec2 polygonPosition = body->GetPosition();
  drawPolygon.setRotation((-180.f / M_PI) * body->GetAngle());
  drawPolygon.setPosition(sf::Vector2f(conf::drawScale * polygonPosition.x, -1 * conf::drawScale * (polygonPosition.y)));

  window.draw(drawPolygon);

  //get wheel positions then draw
  b2Vec2 wheelPosition[2];
  float32 wheelAngle[2];
  sf::Vector2f wheelCenter[2];
  for (int i = 0; i < 2; i++)
    {
      wheelPosition[i] = wheelBody[i]->GetWorldCenter();
      wheelCenter[i] = sf::Vector2f(conf::drawScale * wheelPosition[i].x - drawWheel[i].getRadius(), -1 * conf::drawScale * wheelPosition[i].y - drawWheel[i].getRadius());
      drawWheel[i].setPosition(wheelCenter[i]);

      wheelAngle[i] = wheelBody[i]->GetAngle();
      window.draw(drawWheel[i]);
    }

}

Car::~Car()
{
  destroy();
}

void Car::destroy()
{
  for (int i = 0; i < 2; i++)
    {
      world->DestroyJoint(axis[i]);
      world->DestroyBody(wheelBody[i]);
      axis[i] = NULL;
      wheelBody[i] = NULL;
    }
  world->DestroyBody(body);
  body = NULL;
}

b2Vec2 Car::getCenter() const
{
  b2Vec2 position = body->GetWorldCenter();
  return b2Vec2(conf::drawScale * position.x, -1 * conf::drawScale * position.y);
}
