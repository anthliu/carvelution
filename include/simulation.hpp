#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <QtGui>
#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include "qsfmlcanvas.hpp"
#include "ground.hpp"
#include "car.hpp"
#include "population.hpp"
#include "randomgen.hpp"
#include "configurations.hpp"

class Simulation : public QSFMLCanvas
{
public:
  Simulation(QWidget* parent, const QPoint& position, unsigned int frameTime = 0);
private:
  sf::View view;
  b2World world;
  Population population;
  Car car;
  Ground ground;

  b2Vec2 center;
  int carNumber;
  int frames;
  int seconds;
  float32 timeGoal;
  float32 maxDist;
  int extensions;
  float32 extensionUnit;

  virtual void OnInit();
  virtual void OnUpdate();
};
#endif
