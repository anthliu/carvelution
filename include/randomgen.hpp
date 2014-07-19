#ifndef RANDOM_GEN_HPP
#define RANDOM_GEN_HPP

#include <Box2d/Box2d.h>
#include <vector>

float32 randAngleWeight();
float32 randLength();
float32 randWheelLength();
int randWheel();
int randHue();//random hue for random color generation

void extendBaseHilly(std::vector <b2Vec2>& pointSet);

#endif
