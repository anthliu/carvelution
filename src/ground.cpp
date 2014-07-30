#include <Box2d/Box2d.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "ground.hpp"
#include "randomgen.hpp"
#include "configurations.hpp"
#include "simulation.hpp"

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

  //update line
  GSet updateLine;
  for(std::vector<b2Vec2>::size_type index = line.size() + 1; index < point.size(); index++)
    {
      updateLine.tl = sf::Vertex(sf::Vector2f(conf::drawScale * point[index - 1].x, -1 * conf::drawScale * point[index - 1].y));
      updateLine.bl = sf::Vertex(sf::Vector2f(conf::drawScale * point[index - 1].x, -1 * conf::drawScale * point[index - 1].y + conf::groundThickness));
      updateLine.tr = sf::Vertex(sf::Vector2f(conf::drawScale * point[index].x, -1 * conf::drawScale * point[index].y));
      updateLine.br = sf::Vertex(sf::Vector2f(conf::drawScale * point[index].x, -1 * conf::drawScale * point[index].y + conf::groundThickness));

      updateLine.tl.color = sf::Color(randHue(), randHue(), randHue());
      updateLine.bl.color = sf::Color(randHue(), randHue(), randHue());
      updateLine.tr.color = sf::Color(randHue(), randHue(), randHue());
      updateLine.br.color = sf::Color(randHue(), randHue(), randHue());

      line.push_back(updateLine);
    }
}

void Ground::draw(sf::RenderWindow& window)
{
  for(std::vector<GSet>::iterator iter = line.begin(); iter != line.end(); ++iter)
    {
      sf::Vertex drawBox[4] = {(*iter).tl, (*iter).bl, (*iter).tr, (*iter).br};
      window.draw(drawBox, 4, sf::TrianglesStrip);
    }

}

void Ground::draw(Simulation& sim)
{
  for(std::vector<GSet>::iterator iter = line.begin(); iter != line.end(); ++iter)
    {
      sf::Vertex drawBox[4] = {(*iter).tl, (*iter).bl, (*iter).tr, (*iter).br};
      sim.draw(drawBox, 4, sf::TrianglesStrip);
    }

}

void Ground::extend()
{
  extendBaseHilly(point);
  buildBody();
}
