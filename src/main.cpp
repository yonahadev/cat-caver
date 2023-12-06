//
//  main.cpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#include "application.hpp"
#include "glad.h"
#include "glfw3.h"
#include <stdexcept>
#include <iostream>

int main() {
    try {
        runApplication();
    } catch (const std::runtime_error &error) {
        glfwTerminate();
        std::cout << error.what() << "\n";
    }
    std::cout << "Terminating Cat Caver" << "\n";
    return 0;
}
