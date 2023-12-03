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

unsigned int screenWidth = 854;
unsigned int screenHeight = 480;
const char *WINDOW_NAME = "Cat Caver";
constexpr unsigned int HORIZONTAL_TILES = 16;
constexpr unsigned int VERTICAL_TILES = 10;

std::vector<int> tiles = { 5,5,5,5,5,
                            5,5,5,5,5,
                            5,5,5,5,5,
                            5,5,5,5,5,
                            5,5,5,5,5
};

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
    Texture texture("/Users/tom/Documents/cplusplus/cat-caver/res/spritesheet.png",shader.shaderProgram);
    
    Player player(0,0,1);
    
    Terrain terrain(tiles,5,5);
    
    Mat3 orthoMatrix = Mat3::Orthographic((-HORIZONTAL_TILES/2)+0.5,
                                    (HORIZONTAL_TILES/2)+0.5,
                                    (-VERTICAL_TILES/2)+0.5,
                                    (VERTICAL_TILES/2)+0.5
                                    );
 
    
    while (!glfwWindowShouldClose(window.ptr)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        shader.loadUniform(orthoMatrix,"u_Transformation");
        player.buffer.draw();
        
        shader.loadUniform(orthoMatrix*player.matrix,"u_Transformation");
        terrain.buffer.draw();
        
        glfwPollEvents();
        glfwSwapBuffers(window.ptr);
    }
    
    glfwTerminate();
}
