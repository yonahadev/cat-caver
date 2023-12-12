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

int handleMouseMove(GLFWwindow* window,const Vec2 &pos,const Vec2i &screenSize,const Vec2i &aspectRatio,const Terrain &terrain, Mouse &mouse) {
    
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
//    if (mouseX > screenSize.x || mouseX < 0 || mouseY > screenSize.y || mouseY < 0 ) return 0;
    
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
    
    int newX = floor(mouseX);
    int newY = floor(mouseY);
    
    if (newX != mouse.tileX || newY != mouse.tileY) {
        mouse.holding = 0;
    }
    
    mouse.tileX = newX;
    mouse.tileY = newY;
    
    
//    std::cout << "Tile coordinates: " << mouse.tileX << "," << mouse.tileY << "\n";
    
    mouse.currentTile  = terrain.getTile(mouse.tileX, mouse.tileY);
//
//    std::cout << "Current tile is: " << mouse.currentTile << "\n";
    
    if (mouse.currentTile == 4) {
        std::vector<Vertex> vertices;
        generateQuad(mouse.tileX,mouse.tileY,6,vertices);
        mouse.hoverBuffer = VertexBuffer(vertices);

    } else {
        mouse.hoverBuffer = VertexBuffer();
    }
    return 1;
};

void handleMouseHold(GLFWwindow* window,Terrain &terrain, Mouse &mouse, Player &player) {
    if (!mouse.tileX || !mouse.tileY) return;
    int tile = terrain.getTile(mouse.tileX, mouse.tileY);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && terrain.isCollideable(tile)) {
        
        mouse.holding += 16.6667;
        float blockHealth = terrain.getBlockHP(tile);
        
        std::vector<Vertex> vertices;
        float mined = mouse.minedPercentage/100.0f;
        
        float reverse = (1-mined)/2;
        float startX = mouse.tileX+reverse;
        float startY = mouse.tileY+reverse;
        
        generateUIQuad(mined,mined,startX,startY,vertices);
        
        mouse.progressBuffer = VertexBuffer(vertices);
        
        if (mouse.holding > blockHealth) {
            terrain.mineBlock(mouse.tileX, mouse.tileY);
            std::string block = terrain.getBlockName(tile);
            player.blockCounts[block] += 1;
            mouse.holding = 0;
            terrain.generateBuffer();
        }
        mouse.minedPercentage = (mouse.holding/blockHealth)*100;
//        std::cout << "holding mouse button for: " << mouse.holding << "ms \n";
    } else {
        mouse.holding = 0;
    }
}


void handleKeyPress(GLFWwindow *window, Player &player, const Terrain &terrain, float &time) {
    
    float jumpDelay = 0.1f;
    
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
       player.moveCamera(-player.moveSpeed,0,terrain);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            float currentTime = glfwGetTime();
            if (currentTime - time > jumpDelay ) {
                player.jump(terrain);
                time = currentTime;
            }
        }
   } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
       player.moveCamera(player.moveSpeed,0,terrain);
       if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
           float currentTime = glfwGetTime();
           if (currentTime - time > jumpDelay ) {
               player.jump(terrain);
               time = currentTime;
           }
       }
   } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
       float currentTime = glfwGetTime();
       if (currentTime - time > jumpDelay ) {
           player.jump(terrain);
           time = currentTime;
       }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
           player.moveCamera(-player.moveSpeed,0,terrain);
            
            
       } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
           player.moveCamera(player.moveSpeed,0,terrain);
       }
    }
    
    player.accelerate(terrain);
    
    player.collisions = {};
}
        

    
