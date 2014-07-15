#ifndef GROUND_HPP
#define GROUND_HPP

#include <Box2d/Box2d.h>
#include <SFML/Graphics.hpp>
#include <vector>

class Ground
{
  /*Generic Ground class

    todo - add alternative methods of generating the ground*/
  std::vector <b2Vec2> point;//connecting the points makes the ground
  b2Body* body;
  b2World* world;

  void buildBody();//build the ground in b2World / update the ground
public:
  Ground(b2World* setWorld);
  ~Ground;
  void draw(sf::RenderWindow& window);
};

#endif
