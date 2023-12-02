//
//  window.cpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#include "window.hpp"
#include <iostream>

void Window::setupWindow(const unsigned int width, const unsigned int height, const char *name) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    ptr = glfwCreateWindow(width,height,name,NULL, NULL);
    if (ptr == NULL) {
        glfwTerminate();
        std::cout << "Failed to create GLFW window" << "\n";
    }
    glfwMakeContextCurrent(ptr);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        std::cout << "Failed to initialize GLAD" << "\n";
    }
}

Window::Window(const unsigned int width, const unsigned int height, const char *name) {
    setupWindow(width,height,name);
}
