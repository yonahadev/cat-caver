//
//  math.hpp
//  Executable
//
//  Created by tom on 2023/10/10.
//

#ifndef math_hpp
#define math_hpp

#include <stdio.h>
#include <cmath>
#include "vec2.hpp"

float radians(float degrees);
int getHCF(int number1, int number2);
int min(int number1, int number2);
int getRandomInt(int lower,int higher);
float calculateDistance(const Vec2i &start,const Vec2i &end);

#endif /* math_hpp */
