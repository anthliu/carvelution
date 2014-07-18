#include <Box2d/Box2d.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "ground.hpp"
#include "randomgen.hpp"
#include "configurations.hpp"

Ground::Ground(b2World* setWorld) : point(3)
{
  world = setWorld;

  //first initialize the starting point of the car
  point[0] = b2Vec2(-10.0f, -1 * conf::maxLength);
  point[1] = b2Vec2(-5.0f, -1 * conf::maxLength);
  point[2] = b2Vec2(0.0f, -1 * conf::maxLength);

  extendBaseHilly(point);

  buildBody();
}

Ground::~Ground()
{
}

void Ground::buildBody()
{
  b2ChainShape chain;
  chain.CreateChain(&point[0], point.size());
  chain.SetPrevVertex(b2Vec2(point[0].x - 4.0f, point[0].y));
  chain.SetNextVertex(b2Vec2(point.back().x + 4.0f, point.back().y));

  b2BodyDef bodyDef;
  body = world->CreateBody(&bodyDef);
  body->CreateFixture(&chain, 0.0f);
}

void Ground::draw(sf::RenderWindow& window)
{
  sf::Vertex line[2];
  for(std::vector<b2Vec2>::size_type index = 1; index < point.size(); index++)
    {
      line[0] = sf::Vertex(sf::Vector2f(conf::drawScale * point[index - 1].x, -1 * conf::drawScale * point[index - 1].y));
      line[1] = sf::Vertex(sf::Vector2f(conf::drawScale * point[index].x, -1 * conf::drawScale * point[index].y));
      line[0].color = sf::Color::Black;
      line[1].color = sf::Color::Black;

      window.draw(line, 2, sf::Lines);
    }

}
