#ifndef GENOME_HPP
#define GENOME_HPP

#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>

class Genome
{
  /*attributes to make a complete car
   The "genes" of a car*/
public:
  float32 legAngleWeight[8];
  float32 legLength[8];
  int wheelLeg[2];
  float32 wheelLength[2];
  sf::Color color;

  Genome();//random genome
  Genome(float32 setAngleWeight[8], float32 setLegLength[8], int setWheelLeg[2], float32 wheelLength[2], sf::Color setColor);

  void mutate(float32 mutateRate);//mutate all attributes at a chance (mutateRate)

  void mutateLegAngleWeight(int number);//number: which legAngle to mutate
  void mutateLegLength(int number);
  void mutateWheelLeg(int number);
  void mutateWheelLength(int number);
  void mutateColor();
};

#endif
