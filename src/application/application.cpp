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



const char *WINDOW_NAME = "Cat Caver";

Vec2i screenSize = {854,480};
Vec2i aspectRatio = {16,10};

Mat3 textMatrix = Mat3::Orthographic(0, screenSize.x, 0, screenSize.y);

std::vector<int> startingTiles = { 
    1,1,1,1,1,1,1,1,1,1,
    1,3,3,3,3,3,3,3,3,1,
    1,3,3,3,3,3,3,3,3,1,
    1,3,3,3,3,3,3,3,3,1,
    1,4,4,4,4,4,4,4,4,1,
};

std::vector<std::string> urls = {
    "/Users/tom/Documents/cplusplus/cat-caver/res/spritesheet.png",
    "/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.png"
};

int width = 10;
int height = static_cast<int>(startingTiles.size()/width);

void handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
};

void resizeWindow(GLFWwindow* window, int width, int height) {
    screenSize = {width,height};
    textMatrix = Mat3::Orthographic(0, screenSize.x, 0, screenSize.y);
    glViewport(0, 0, width, height);
}


void runApplication() {
    
    Window window(screenSize,WINDOW_NAME);
    
    
    glfwSetKeyCallback(window.ptr, handleKeypress);
    glfwSetWindowSizeCallback(window.ptr, resizeWindow);
    
    Shader shader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/vertex.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/fragment.glsl");
    Texture texture(urls);
    
    Text text("/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.fnt");
    
    Player player(1,-3,7);
    
    Terrain terrain(startingTiles,width,height);
    
    Mat3 orthoMatrix = Mat3::Orthographic(
                                          (-aspectRatio.x/2)+0.5,
                                          (aspectRatio.x/2)+0.5,
                                          (-aspectRatio.y/2)+0.5,
                                          (aspectRatio.y/2)+0.5
                                          );
    
    
    Mouse mouse;
    
    
    float time = glfwGetTime();
    
    while (!glfwWindowShouldClose(window.ptr)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        int depth = int(abs(floor(player.coordinates.y)));
        
        if (depth > terrain.height-3) {
            terrain.generateLayer();
        }
        
//        std::cout << std::string(screenSize) << "\n";
        
        
        handleMouseMove(window.ptr, player.coordinates, screenSize, aspectRatio,terrain,mouse);
        handleMouseHold(window.ptr,terrain,mouse);
        handleKeyPress(window.ptr, player,terrain,time);
        
        
        //order does matter of multiplication...
        texture.setTexture("spritesheet");
        shader.loadMatrix(orthoMatrix*player.matrix,"u_Transformation");
        terrain.buffer.draw();
        shader.loadInt(false, "u_IsTexture");
        
        
        if (mouse.holding > 0) {
            shader.loadVec4(1.0, 0.3, 1.0, 0.7, "u_QuadColour");
//            std::cout << mouse.minedPercentage << "\n";
            mouse.progressBuffer.draw();
        } else {
            shader.loadVec4(0.2, 0.3, 0.1, 0.3, "u_QuadColour");
            mouse.hoverBuffer.draw();
        }
        
        shader.loadInt(true, "u_IsTexture");
        shader.loadMatrix(orthoMatrix,"u_Transformation");
        player.buffer.draw();
        
        texture.setTexture("fontImg");
        shader.loadMatrix(textMatrix, "u_Transformation");
        shader.loadInt(true, "u_IsTexture");
        text.renderText("Depth: " + std::to_string(depth), 50, screenSize.y-50);
        
        
        glfwPollEvents();
        glfwSwapBuffers(window.ptr);
    }
    
    glfwTerminate();
}
