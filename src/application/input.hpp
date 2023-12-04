//
//  windowUtils.hpp
//  Executable
//
//  Created by tom on 2023/10/19.
//

#ifndef input_hpp
#define input_hpp

#include <stdio.h>
#include "glad.h"
#include "glfw3.h"
#include "mat3.hpp"
#include "player.hpp"
#include "vec2.hpp"
#include "terrain.hpp"

void calculateMousePosition(GLFWwindow* window,const Vec2 &pos,const Vec2 &screenSize,const Vec2 &aspectRatio, const Terrain &terrain);

void processInput(GLFWwindow *window, Player &player, const Terrain &dungeon);

#endif /* windowInput_hpp */
