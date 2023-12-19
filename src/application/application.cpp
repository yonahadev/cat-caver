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
#include "vec2.hpp"
#include "vec4.hpp"
#include "text.hpp"
#include <fstream>
#include <unordered_map>
#include "dungeonConfig.hpp"
#include "block.hpp"
#include "quad.hpp"
#include "gui.hpp"
#include "button.hpp"

const char *WINDOW_NAME = "Cat Caver";

Vec2i screenSize = {854,480};
Vec2i aspectRatio = {16,10};
Vec2f windowScale = {1,1};


Mat3 guiMatrix = Mat3::Orthographic(0, screenSize.x, 0, screenSize.y);

std::vector<std::string> urls = {
    "/Users/tom/Documents/cplusplus/cat-caver/res/spritesheet.png",
    "/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.png"
};

bool lightingOn = true;

void handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(key == GLFW_KEY_1 && action == GLFW_PRESS){
        lightingOn = !lightingOn;
    }
}

void resizeWindow(GLFWwindow* window, int width, int height) {
    glfwGetWindowContentScale(window, &windowScale.x, &windowScale.y);
    screenSize = {width,height};
    guiMatrix = Mat3::Orthographic(0, screenSize.x, 0, screenSize.y);
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
    
    glfwGetWindowContentScale(window.ptr, &windowScale.x, &windowScale.y);
    
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
    
    //enum maps directly to the colour vector
    
    enum colours {
        white,
        black,
        grey,
        red,
        green,
        blue
    };
    
    std::vector<Vec4f> colourVector = {
        {1.0f,1.0f,1.0f,1.0f},
        {0.0f,0.0f,0.0f,1.0f},
        {0.0f,0.0f,0.0f,0.7f},
        {1.0f,0.0f,0.0f,0.7f},
        {0.0f,1.0f,0.0f,0.7f},
        {0.0f,0.0f,1.0f,0.7},
    };
    
    Gui gui("/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.fnt",colourVector);
    
    Mouse mouse;

    std::vector<Vertex> vertices;
    generateUIQuad(16, 10, (-aspectRatio.x/2)+0.5, (-aspectRatio.y/2)+0.5, vertices);
    VBO lightVBO = VBO();
    VAO lightVAO = VAO();
    lightVAO.bindArray();
    lightVBO.bindBuffer();
    lightVBO.bindData(vertices);
    lightVAO.enableAttributes();
    lightVAO.unbindArray();
    
    float time = glfwGetTime();
    
    std::vector<Button> buttons;
    
    Button surface;
    surface.text = "surface";
    surface.width = gui.getWidth("surface");
    surface.height = 40;
    surface.x = 50;
    surface.y = screenSize.y - 100;
    
    buttons.push_back(surface);
    
    
    while (!glfwWindowShouldClose(window.ptr)) {
        glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        int depth = int(abs(floor(player.coordinates.y)));
//        
        if (depth > terrain.height-3) {
            terrain.generateLayer();
        }
//
        
        handleMouseMove(window.ptr, player.coordinates, screenSize, aspectRatio,terrain,mouse,player);
        handleMining(window.ptr,terrain,mouse,player);
        handleKeyPress(window.ptr, player,terrain,time);
        handleGUI(window.ptr, terrain, mouse, player, buttons, screenSize);
        
        shader.loadUniform<Vec4f>(colourVector[white], "u_QuadColour");
        shader.loadUniform<int>(true, "u_IsTexture");
        texture.setTexture("spritesheet");
        shader.loadUniform<Mat3>(orthoMatrix*player.matrix,"u_Transformation");
        terrain.vao.bindArray();
        terrain.vbo.draw();
        
        shader.loadUniform<int>(true, "u_IsTexture");
        shader.loadUniform<Mat3>(orthoMatrix,"u_Transformation");
        player.vao.bindArray();
        player.vbo.draw();
        
        mouse.generateBuffer(blockData);
        if (mouse.vbo.verticesCount > 0) {
            shader.loadUniform<Mat3>(orthoMatrix*player.matrix,"u_Transformation");
            shader.loadUniform<int>(false, "u_IsTexture");
            if (mouse.backpackFull && mouse.holding > 0) {
                shader.loadUniform<Vec4f>(colourVector[red], "u_QuadColour");
            } else {
                shader.loadUniform<Vec4f>(colourVector[grey], "u_QuadColour");
            }
            mouse.vao.bindArray();
            mouse.vbo.draw();
        }
        
        if (lightingOn) {
            Vec2f size = {static_cast<float>(screenSize.x*windowScale.x),static_cast<float>(screenSize.y*windowScale.y)};
            int lightRadius = screenSize.x/3;
            if (depth < 5) {
                lightRadius = screenSize.x;
            }
            shader.loadUniform<Vec2f>(size, "u_ScreenSize");
            shader.loadUniform<int>(lightRadius, "u_LightRadius");
            shader.loadUniform<int>(false, "u_IsTexture");
            shader.loadUniform<Mat3>(orthoMatrix, "u_Transformation");
            shader.loadUniform<Vec4f>(colourVector[white], "u_QuadColour");
            lightVAO.bindArray();
            lightVBO.draw();
            shader.loadUniform<int>(0, "u_LightRadius");
        }
        
//        std::cout << player.backpackCount << "\n";
        shader.loadUniform<Mat3>(guiMatrix, "u_Transformation");
        
        gui.renderButton(surface.text, surface.x, surface.y, surface.height, texture, shader,red,white);
//        gui.renderText("Depth: " + std::to_string(depth), 50, screenSize.y-100, texture,shader,white);
        
//        shader.loadUniform<int>(true, "u_IsTexture");
//        text.renderText("Backpack: " + std::to_string(player.backpackCount)+"/"+std::to_string(player.backpackCapacity), 50, screenSize.y-100);
//        shader.loadUniform<Vec4f>(mouseInvalid, "u_QuadColour");
//        if (mouse.backpackFull && mouse.holding > 0) {
//            
//            text.renderText("Backpack is full", 50, screenSize.y-150);
//        }
//        int count = 0;
//        for (auto &block: player.blockCounts) {
//            int offset = count*50;
//            text.renderText(block.first+ ": " + std::to_string(block.second), 50, screenSize.y-150-offset);
//            count++;
//        }
        
        
        glfwPollEvents();
        glfwSwapBuffers(window.ptr);
    }
    

    glfwTerminate();
}
