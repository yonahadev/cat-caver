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
#include "vec2i.hpp"
#include "terrain.hpp"
#include "vertex.hpp"
#include "mouse.hpp"

void handleMouseMove(GLFWwindow* window,const Vec2 &pos,const Vec2i &screenSize,const Vec2i &aspectRatio, const Terrain &terrain, Mouse &mouse);

void handleMouseHold(GLFWwindow* window,Terrain &terrain, Mouse &mouse, Player &player);

void handleKeyPress(GLFWwindow *window, Player &player, const Terrain &dungeon, float &time);

#endif /* windowInput_hpp */
