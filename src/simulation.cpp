#include <QtGui>
#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include "qsfmlcanvas.hpp"
#include "simulation.hpp"
#include "car.hpp"
#include "ground.hpp"
#include "population.hpp"
#include "randomgen.hpp"
#include "configurations.hpp"

Simulation::Simulation(QWidget* parent, const QPoint& position, unsigned int frameTime) :
  QSFMLCanvas(parent, position, QSize(conf::windowHeight, conf::windowLength)), view(sf::FloatRect(-300.0, 0, conf::windowHeight, conf::windowLength)), world(conf::gravity), population(conf::populationSize), car(population.car[0], &world), ground(&world)
{
  carNumber = 0;//testing which car in population
  frames = 0;
  seconds = -1;//gives the car more time in the start of the simulation
  timeGoal = 0;//if the maxDist is not greater than timeGoal in conf::timeLimit, than end the car trial
  maxDist = 0;
  extensions = 0;
  extensionUnit = conf::drawScale * ((float32)conf::extendNumber * conf::extendUnitLength);
}

void Simulation::OnInit()
{

}

void Simulation::OnUpdate()
{
  center = car.getCenter();
  if (center.x > maxDist)
    //update maxDist
    {
      maxDist = center.x;
      if (maxDist >= extensions * extensionUnit + extensionUnit / 2)
	//update and extend ground
	{
	  extensions++;
	  ground.extend();
	}
    }
  frames++;
  if (frames == conf::fps)
    {
      frames = 0;
      seconds++;
      if (seconds == conf::timeLimit)
	//if the counter is on the timeLimit, check if the car went furthur on the ground; if it didn't, than go to the next car
	{
	  seconds = 0;
	  if (maxDist <= timeGoal + 10)
	    {
	      //next Car checks and steps
	      if (maxDist <= conf::minScore)
		maxDist = conf::minScore;
	      else
		population.score[carNumber] = maxDist;
	      carNumber++;
	      if (carNumber == conf::populationSize)
		{
		  carNumber = 0;
		  population.passOn();
		}
	      seconds = -1;
	      maxDist = 0;
	      timeGoal = 0;
	      car.destroy();
	      car.reset(population.car[carNumber]);
	      center = car.getCenter();
	    }
	  else
	    {
	      timeGoal = maxDist;
	    }
	}
    }

  view.setCenter(center.x, center.y);
  setView(view);
  clear(sf::Color::White);
  world.Step(conf::timeStep, conf::velocityIterations, conf::positionIterations);
  car.draw(*this);
  ground.draw(*this);
}
