//
//  application.cpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#include "application.hpp"
#include "glad.h"
#include "glfw3.h"
#include <iostream>
#include "window.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "player.hpp"
#include "mat3.hpp"
#include <vector>
#include <string>
#include "input.hpp"
#include "mouse.hpp"
#include "vec2i.hpp"
#include "text.hpp"
#include <fstream>
#include <unordered_map>
#include "dungeonConfig.hpp"
#include "block.hpp"

const char *WINDOW_NAME = "Cat Caver";

Vec2i screenSize = {854,480};
Vec2i aspectRatio = {16,10};

Mat3 textMatrix = Mat3::Orthographic(0, screenSize.x, 0, screenSize.y);

std::vector<std::string> urls = {
    "/Users/tom/Documents/cplusplus/cat-caver/res/spritesheet.png",
    "/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.png"
};

void handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void resizeWindow(GLFWwindow* window, int width, int height) {
    screenSize = {width,height};
    textMatrix = Mat3::Orthographic(0, screenSize.x, 0, screenSize.y);
    glViewport(0, 0, width, height);
}


void runApplication() {
    
    //level -1 means you can't mine it / it isn't collideable
    std::vector<Block> blockData = {
        {"stone",1,1000},
        {"copper",2,1500},
        {"iron",2,1500},
        {"dirt",-1,1000},
        {"coal",2,1250},
        {"gold",3,2000},
        {"diamond",3,3000},
    };
    
    
    Window window(screenSize,WINDOW_NAME);
    
    DungeonConfig dungeonConfig;
    dungeonConfig.width = 16;
    dungeonConfig.startingAliveChance = 45;
    dungeonConfig.overpopulationCount = 9;
    dungeonConfig.underpopulationCount = 3;
    dungeonConfig.cellsForBirth = 4;
    dungeonConfig.turnCount = 0;
    
    glfwSetKeyCallback(window.ptr, handleKeypress);
    glfwSetWindowSizeCallback(window.ptr, resizeWindow);
    
    Shader shader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/vertex.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/fragment.glsl");
    Texture texture(urls);
    
    Text text("/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.fnt");
    
    std::unordered_map<std::string, int> map;
    for (Block &block: blockData) {
        std::string blockName = block.name;
        if (block.level != -1) {
            map[blockName] = 0;
        }
    }
    
    Player player(1,-3,7,map);
    
    Terrain terrain(dungeonConfig,blockData);
    
    Mat3 orthoMatrix = Mat3::Orthographic(
                                          (-aspectRatio.x/2)+0.5,
                                          (aspectRatio.x/2)+0.5,
                                          (-aspectRatio.y/2)+0.5,
                                          (aspectRatio.y/2)+0.5
                                          );
    
    
    Mouse mouse;

    float time = glfwGetTime();
    
    while (!glfwWindowShouldClose(window.ptr)) {
        glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        int depth = int(abs(floor(player.coordinates.y)));
//        
        if (depth > terrain.height-3) {
            terrain.generateLayer();
        }
//        
        handleMouseMove(window.ptr, player.coordinates, screenSize, aspectRatio,terrain,mouse);
        handleMouseHold(window.ptr,terrain,mouse,player);
        handleKeyPress(window.ptr, player,terrain,time);
        
        shader.loadInt(true, "u_IsTexture");
        texture.setTexture("spritesheet");
        shader.loadMatrix(orthoMatrix*player.matrix,"u_Transformation");
        terrain.vao.bindArray();
        terrain.vbo.draw();
        
//
//        shader.loadMatrix(orthoMatrix,"u_Transformation");
        
        shader.loadInt(false, "u_IsTexture");
        shader.loadVec4(1.0, 0.3, 1.0, 0.7, "u_QuadColour");
        mouse.generateBuffer(blockData);
        if (mouse.vbo.verticesCount > 0) {
            mouse.vao.bindArray();
            mouse.vbo.draw();
        }
        
//        if (mouse.holding > 0) {
//        } else {
//            shader.loadVec4(0.2, 0.3, 0.1, 0.3, "u_QuadColour");
//            mouse.hoverBuffer.draw();
//        }
         
        shader.loadInt(true, "u_IsTexture");
        shader.loadMatrix(orthoMatrix,"u_Transformation");
        player.vao.bindArray();
        player.vbo.draw();

        texture.setTexture("fontImg");
        shader.loadMatrix(textMatrix, "u_Transformation");
        shader.loadInt(true, "u_IsTexture");
        text.renderText("Depth: " + std::to_string(depth), 50, screenSize.y-50);
        int count = 0;
        for (auto &block: player.blockCounts) {
            int offset = count*50;
            text.renderText(block.first+ ": " + std::to_string(block.second), 50, screenSize.y-100-offset);
            count++;
        }
        
        
        glfwPollEvents();
        glfwSwapBuffers(window.ptr);
    }
    
    glfwTerminate();
}
