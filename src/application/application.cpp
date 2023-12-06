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
#include "input.hpp"
#include "mouse.hpp"
#include "vec2i.hpp"
#include "text.hpp"


float screenWidth = 854.0f;
float screenHeight = 480.0f;

const char *WINDOW_NAME = "Cat Caver";
constexpr float HORIZONTAL_TILES = 16.0f;
constexpr float VERTICAL_TILES = 10.0f;

Vec2 screenSize = {screenWidth,screenHeight};
Vec2 aspectRatio = {HORIZONTAL_TILES,VERTICAL_TILES};

std::vector<int> startingTiles = { 
    1,1,1,1,1,1,1,1,1,1,
    1,3,3,3,3,3,3,3,3,1,
    1,3,3,3,3,3,3,3,3,1,
    1,3,3,3,3,3,3,3,3,1,
    1,4,4,4,4,4,4,4,4,1,
};

int width = 10;
int height = static_cast<int>(startingTiles.size()/width);

void handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
};

void resizeWindow(GLFWwindow* window, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
}

void runApplication() {
    
    Window window(screenWidth,screenHeight,WINDOW_NAME);
    
    
    glfwSetKeyCallback(window.ptr, handleKeypress);
    glfwSetFramebufferSizeCallback(window.ptr, resizeWindow);
    
    Shader shader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/vertex.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/fragment.glsl");
//    Texture texture("/Users/tom/Documents/cplusplus/cat-caver/res/spritesheet.png",shader.shaderProgram);
    Texture texture("/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.png",shader.shaderProgram);
    
    Text text("/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.fnt");
    
    Player player(0,0,7);
    
    
    Terrain terrain(startingTiles,width,height);
    
    Mat3 orthoMatrix = Mat3::Orthographic(
                                          (-HORIZONTAL_TILES/2)+0.5,
                                          (HORIZONTAL_TILES/2)+0.5,
                                          (-VERTICAL_TILES/2)+0.5,
                                          (VERTICAL_TILES/2)+0.5
                                          );
    
    Mat3 textMatrix = Mat3::Orthographic(0, screenWidth, 0, screenHeight);
    
    
    Mouse mouse;
    
    
    float time = glfwGetTime();
    
    while (!glfwWindowShouldClose(window.ptr)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        int depth = abs(floor(player.coordinates.y));
        
        if (depth > terrain.height-3) {
            terrain.generateLayer();
        }
        
        handleMouseMove(window.ptr, player.coordinates, screenSize, aspectRatio,terrain,mouse);
        handleMouseHold(window.ptr,terrain,mouse);
        handleKeyPress(window.ptr, player,terrain,time);
        
        
        //order does matter of multiplication...
        shader.loadMatrix(orthoMatrix*player.matrix,"u_Transformation");
//        terrain.buffer.draw();
//        shader.loadBool(false, "u_IsTexture");
//        mouse.buffer.draw();
//        shader.loadBool(true, "u_IsTexture");
//        shader.loadMatrix(orthoMatrix,"u_Transformation");
//        player.buffer.draw();
        
        shader.loadMatrix(textMatrix, "u_Transformation");
        shader.loadBool(true, "u_IsTexture");
        text.renderText("The quick brown fox jumps over the lazy dog", 0, 10);
        text.renderText("JOHNCOOK IS 23002304203403212387", 0, 400);
        
        
        glfwPollEvents();
        glfwSwapBuffers(window.ptr);
    }
    
    glfwTerminate();
}
