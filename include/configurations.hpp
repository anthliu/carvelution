#ifndef CONFIGURATIONS_HPP
#define CONFIGURATIONS_HPP

namespace conf
{
  const int windowLength = 480;
  const int windowHeight = 640;
  const int fps = 60;
  const float32 timeStep = 1.0f / (float32)fps;
  const int velocityIterations = 8;
  const int positionIterations = 4;

  const b2Vec2 gravity(0.0f, -18.0f);

  const float32 minAngleWeight = 0.10f;
  const float32 maxLength = 5.0f;
  const int maxWheelSize = 3;

  const float32 carDensity = 2.0f;
  const float32 carFriction = 0.7f;
  const float32 carRestitution = 0.0f;

  const float32 wheelLocationRatio = 7.0f / 8.0f;
  const float32 wheelDensity = 0.5f;
  const float32 wheelFriction = 0.9f;
  const float32 wheelRestitution = 0.0f;

  const float32 axisSpeed = -2000.0f;
  const float32 maxTorque = 500.0f;

  const int drawScale = 30;
  const int drawBorder = 3;
  const int groundThickness = 20;

  const int extendNumber = 10;
  const float32 extendUnitLength = 4.0;

  const float32 baseHillyChange = 2.0f;

  const int timeLimit = 1;
  const float32 mutationRate = 0.05f;
  const int populationSize = 20;
  const float32 minScore = 0.5f;
}

#endif
