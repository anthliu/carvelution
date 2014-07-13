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

  b2Vec2 gravity(0.0, -10.0f);

  float32 minAngleWeight = 0.02f;
  float32 maxLength = 10.0f;

  float32 carDensity = 1.0f;
  float32 carFriction = 0.03f;
  float32 carRestitution = 0.0f;

  int drawScale = 10;
}

#endif
