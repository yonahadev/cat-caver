//
//  windowUtils.cpp
//  Executable
//
//  Created by tom on 2023/10/19.
//

#include "input.hpp"
#include "glad.h"
#include "glfw3.h"
#include <iostream>
#include "mat3.hpp"
#include "math.hpp"
#include "vertex.hpp"
#include <sstream>
#include <vector>
#include "quad.hpp"

VertexBuffer calculateMousePosition(GLFWwindow* window,const Vec2 &pos,const Vec2 &screenSize,const Vec2 &aspectRatio,const Terrain &terrain) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
    float xMultiplier = screenSize.x/aspectRatio.x;
    float yMultiplier = screenSize.y/aspectRatio.y;

    mouseX *= 1/xMultiplier;
    mouseY *= 1/yMultiplier;
    
    mouseX -= aspectRatio.x*0.5;
    mouseY -= aspectRatio.y*0.5;
    
    mouseY *=  -1;
    
    mouseX += pos.x;
    mouseY += pos.y;
    
    mouseX += 0.5;
    mouseY += 0.5;
    
//    std::cout << "Mouse coordinates: " << mouseX << "," << mouseY << "\n";
    
    int tileX = floor(mouseX);
    int tileY = floor(mouseY);
    
    
//    std::cout << "Tile coordinates: " << tileX << "," << tileY << "\n";
    
    int currentTile = terrain.getTile(tileX, tileY);
//    
//    std::cout << "Current tile is: " << currentTile << "\n";
    
    
    if (currentTile == 4) {
        std::vector<Vertex> vertices;
        generateQuad(tileX,tileY,6,vertices);
        VertexBuffer highlight(vertices);
        return highlight;

    }
    return VertexBuffer();
};

void processInput(GLFWwindow *window, Player &player, const Terrain &terrain) {
    

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
       player.moveCamera(-player.moveSpeed,0,terrain);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            player.jump(terrain);
        }
   } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
       player.moveCamera(player.moveSpeed,0,terrain);
       if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
           player.jump(terrain);
       }
   } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
       player.jump(terrain);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
           player.moveCamera(-player.moveSpeed,0,terrain);
            
            
       } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
           player.moveCamera(player.moveSpeed,0,terrain);
       }
    }
    
    player.accelerate(terrain);
    
    player.colliding = false;
}
        

    
