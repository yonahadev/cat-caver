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

void calculateCoordinates(GLFWwindow* window,Vec2 coordinateOffset);

void processInput(GLFWwindow *window, Player &player, const Terrain &dungeon);

#endif /* windowInput_hpp */
