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

  const b2Vec2 gravity(0.0f, -10.0f);

  const float32 minAngleWeight = 0.05f;
  const float32 maxLength = 5.0f;

  const float32 carDensity = 1.0f;
  const float32 carFriction = 0.03f;
  const float32 carRestitution = 0.0f;

  const int drawScale = 40;
}

#endif
