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
#include "vec2.hpp"
#include "terrain.hpp"

#include "mouse.hpp"
#include "button.hpp"
#include "backpack.hpp"
#include "gui.hpp"

void handleMouseMove(GLFWwindow* window,const Vec2i &screenSize,const Vec2i &aspectRatio, const Terrain &terrain, Mouse &mouse, const Player &player);

void handleMining(GLFWwindow* window,Terrain &terrain, Mouse &mouse, Player &player, GUI &gui);

void handleGUI(GLFWwindow* window,Terrain &terrain, Mouse &mouse, Player &player,const std::vector<Button> &buttons, const Vec2i &screenSize,bool mousePressed, GUI &gui, const bool atSurface);

void handleKeyPress(GLFWwindow *window, Player &player, const Terrain &dungeon, float &time);

#endif /* windowInput_hpp */
