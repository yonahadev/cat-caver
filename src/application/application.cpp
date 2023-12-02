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

unsigned int screenWidth = 854;
unsigned int screenHeight = 480;
const char *WINDOW_NAME = "Cat Caver";

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
    
    while (!glfwWindowShouldClose(window.ptr)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window.ptr);
    }
    
    glfwTerminate();
}
