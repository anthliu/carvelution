#include <Box2d/Box2d.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "ground.hpp"
#include "configurations.hpp"

Ground::Ground(b2World* setWorld) : point(3)
{
  world = setWorld;

  //first initialize the starting point of the car
  point[0] = b2Vec2(-4.0f, -2 * conf::maxLength);
  point[1] = b2Vec2(0.0f, -2 * conf::maxLength);
  point[2] = b2Vec2(4.0f, -2 * conf::maxLength);

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
  std::vector <sf::Vertex> line(point.size());
  for(std::vector<b2Vec2>::size_type index = 0; index < point.size(); index++)
    {
      line[index] = sf::Vertex(sf::Vector2f(conf::drawScale * point[index].x, -1 * conf::drawScale * point[index].y));
      line[index].color = sf::Color::Black;
    }
  window.draw(&line[0], point.size(), sf::Lines);
}
