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
#include "movement.hpp"
#include "vec2.hpp"

void calculateCoordinates(GLFWwindow* window,Vec2 pos) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    if (mouseX < 800 & mouseY < 800 & mouseX > 0 & mouseY > 0) {
        //makes the centre of the screen 0,0 and cartesian coordinate system
        mouseX -= 400;
        mouseY -= 400;
        mouseY *= -1;
//        std::cout << "Window coordinates: " << mouseX << " " << mouseY << "\n";
        std::cout << "Mouse coordinates: " << (mouseX/pos.x) << " " << (mouseY/pos.y) << "\n";
    };
};

//void processInput(GLFWwindow *window, Player &player, const Terrain &dungeon) {
//
//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        moveCamera(viewMatrix, -cameraSpeed, 0,player,dungeon);
//    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        moveCamera(viewMatrix, cameraSpeed, 0,player,dungeon);
//    }
//}
//        player.colliding = false;
//        
//    }
    