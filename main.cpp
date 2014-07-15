#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>
#include <stdio.h>
#include <random>
#include <time.h>
#include "car.hpp"
#include "ground.hpp"
#include "configurations.hpp"

int main()
{
  srand(time(NULL));

  sf::RenderWindow window(sf::VideoMode(conf::windowHeight, conf::windowLength), "Carvelution");
  sf::View view(sf::FloatRect(0, 0, conf::windowHeight, conf::windowLength));
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(conf::fps);
  
  b2World world(conf::gravity);
  b2Vec2 center;
  Car car(&world);
  Ground ground(&world);

  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
        {
          if (event.type == sf::Event::Closed)
            window.close();
        }

      center = car.getCenter();
      view.setCenter(center.x, center.y);
      //window.setView(view);
      window.clear(sf::Color::White);
      world.Step(conf::timeStep, conf::velocityIterations, conf::positionIterations);
      car.draw(window);
      window.display();
    }

  return 0;
}
