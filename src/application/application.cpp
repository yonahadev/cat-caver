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

constexpr unsigned int SCREEN_WIDTH = 854;
constexpr unsigned int SCREEN_HEIGHT = 480;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
};

int runApplication() {
    Window window(SCREEN_WIDTH,SCREEN_HEIGHT,"Cat Caver");
    
    glfwSetKeyCallback(window.ptr, keyCallback);
    
    while (!glfwWindowShouldClose(window.ptr)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window.ptr);
    }
    glfwTerminate();
    return 0;
}
