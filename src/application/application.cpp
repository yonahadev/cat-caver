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
#include "pickaxe.hpp"
#include "backpack.hpp"
#include "PerlinNoise.hpp"

const char *WINDOW_NAME = "Cat Caver";

Vec2i screenSize = {900,563};
Vec2i aspectRatio = {16,10};
Vec2f windowScale = {1,1};

bool mousePressed = false;


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

void handleMouseButton(GLFWwindow* window, int button, int action, int mods ) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mousePressed = true;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        mousePressed = false;
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
        {"stone",1,1000,1},
        {"copper",2,1500,5},
        {"iron",2,1500,5},
        {"dirt",-1,1000,0},
        {"coal",2,1250,3},
        {"gold",3,2000,10},
        {"diamond",3,3000,50},
    };
    
    std::vector<Pickaxe> pickaxeData = {
        {"Ol' trusty",1,1,0},
        {"Shovel",1,3,10},
        {"Fork",2,6,500}
    };
    
    std::vector<Backpack> backpackData = {
        {"pockets",5,0},
        {"sack",15,15},
        {"fat sack", 50, 500}
    };
    
    Window window(screenSize,WINDOW_NAME);
    
    glfwGetWindowContentScale(window.ptr, &windowScale.x, &windowScale.y);
    
    DungeonConfig dungeonConfig;
    dungeonConfig.width = 16;
    dungeonConfig.powerupChance = 1; //applied post layer generation
    dungeonConfig.overpopulationCount = 5;
    dungeonConfig.underpopulationCount = 0;
    dungeonConfig.cellsForBirth = 1;
    dungeonConfig.turnCount = 0;
    dungeonConfig.layerInfo = {
        { //layer one info right side is % chance of spawning
            {0,0.6},
            {1,0.2},
            {2,0.1},
            {4,0.1}
        }
    };
    
    glfwSetKeyCallback(window.ptr, handleKeypress);
    glfwSetWindowSizeCallback(window.ptr, resizeWindow);
    glfwSetMouseButtonCallback(window.ptr, handleMouseButton);
    
    Shader shader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/vertex.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/fragment.glsl");
    Texture texture(urls);
    


    
    std::unordered_map<Block, int> map;
    for (Block &block: blockData) {
        std::string blockName = block.name;
        if (block.level != -1) {
            map[block] = 0;
        }
    }
    
    Player player(1,-3,8,map);
    
    player.ownedPickaxes[pickaxeData[0]] = true;
    player.equippedPickaxe = pickaxeData[0];
    player.ownedBackpacks[backpackData[0]] = true;
    player.equippedBackpack = backpackData[0];
    
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
        {0.3f,0.3f,0.3f,0.7f},
        {1.0f,0.0f,0.0f,0.7f},
        {0.0f,1.0f,0.0f,0.7f},
        {0.0f,0.0f,1.0f,0.7f},
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
    
    
    std::cout << player.equippedPickaxe.name << "\n";
    
    std::string openMenu = "";
    std::string selectedTab = "pickaxes";
    
    float keyTime = glfwGetTime();
    
    std::unordered_map<int,bool> visibleButtons = {
        {0,true},
        {1,true},
        {2,true},
        {3,false},
        {4,false},
        {5,false}
    };
    
    
    while (!glfwWindowShouldClose(window.ptr)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        int depth = int(abs(floor(player.coordinates.y)));
//
        if (depth > terrain.height-3) {
            terrain.generateLayer();
        }
        
        bool atSurface = depth <= 4;
        if (atSurface == false) {
            openMenu = "";
            visibleButtons[3] = false;
            visibleButtons[4] = false;
            visibleButtons[5] = false;
            
        }
        
        std::vector<Button> buttons = {};
        buttons.emplace_back(0,"surface",gui.getWidth("surface"),40,50,screenSize.y-200,red,white,"");
        buttons.emplace_back(2,"ores",gui.getWidth("ores"),40,50,screenSize.y-300,green,white,"");
        
        if (atSurface) {
            buttons.emplace_back(1,"sell",gui.getWidth("sell"),40,50,screenSize.y-250,blue,white,"");
            buttons.emplace_back(2,"shop",gui.getWidth("shop"),40,50,screenSize.y-350,red,white,"");
        } else {
            buttons.emplace_back(1,"sell",gui.getWidth("sell"),40,50,screenSize.y-250,black,grey,"");
            buttons.emplace_back(2,"shop",gui.getWidth("shop"),40,50,screenSize.y-350,black,grey,"");
        }
        
        
        int pickaxeButtonWidth = gui.getWidth("pickaxes");
        buttons.emplace_back(3,"backpacks",gui.getWidth("backpacks"),30,screenSize.x/2-(300/2)+pickaxeButtonWidth+20,screenSize.y-400,red,white,"");
        buttons.emplace_back(3,"pickaxes",pickaxeButtonWidth,30,screenSize.x/2-(300/2),screenSize.y-400,red,white,"");
        
        int count = 0;
        for (Pickaxe &pickaxe: pickaxeData) {
//            std::cout << "Button for " << pickaxe.name << "\n";
            int offset = count*50;
            auto it = player.ownedPickaxes.find(pickaxe);
            bool owned = it != player.ownedPickaxes.end();
            if (owned) {
                if (player.equippedPickaxe == pickaxe) {
                    int width = gui.getWidth("equipped");
                    buttons.emplace_back(4,"equipped",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,grey,white,std::to_string(count));
                } else {
                    int width = gui.getWidth("equip");
                    buttons.emplace_back(4,"equip",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,blue,white,std::to_string(count));
                }
            } else {
                std::string text = "$"+std::to_string(pickaxe.cost);
                int width = gui.getWidth(text);
                buttons.emplace_back(4,text,width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,green,white,std::to_string(count));
                    
            }

            count++;
        }
        count = 0;
        for (Backpack &backpack: backpackData) {
//            std::cout << "Button for " << pickaxe.name << "\n";
            int offset = count*50;
            if (player.ownedBackpacks[backpack]) {
                if (player.equippedBackpack == backpack) {
                    int width = gui.getWidth("equipped");
                    buttons.emplace_back(5,"equipped",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,grey,white,std::to_string(count));
                } else {
                    int width = gui.getWidth("equip");
                    buttons.emplace_back(5,"equip",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,blue,white,std::to_string(count));
                }
            } else {
                std::string text = "$"+std::to_string(backpack.cost);
                int width = gui.getWidth(text);
                buttons.emplace_back(5,text,width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,green,white,std::to_string(count));
                    
            }

            count++;
        }
        

        
        handleMouseMove(window.ptr, player.coordinates, screenSize, aspectRatio,terrain,mouse,player);
        handleMining(window.ptr,terrain,mouse,player);
        handleKeyPress(window.ptr, player,terrain,keyTime);
        handleGUI(window.ptr, terrain, mouse, player, buttons, screenSize, openMenu,selectedTab, mousePressed,pickaxeData,backpackData, visibleButtons, atSurface);
        
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
                shader.loadUniform<Vec4f>(colourVector[green], "u_QuadColour");
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
        
        gui.renderText("Depth: " + std::to_string(depth), 50, screenSize.y-50, texture,shader,white);
        gui.renderText("Backpack: " + std::to_string(player.backpackCount)+"/"+std::to_string(player.equippedBackpack.capacity), 50, screenSize.y-100, texture, shader, blue);
        gui.renderText("$" + std::to_string(player.money), 50, screenSize.y-150, texture, shader, green);
        
        if (openMenu == "ores") {
            gui.renderQuad(screenSize.x/2-(300/2), screenSize.y-350, 300, 300, texture, shader, blue);
            int count = 0;
            for (auto &[block,value]: player.blockCounts) {
                int offset = count*50;
                gui.renderText(block.name+ ": " + std::to_string(value), screenSize.x/2-(300/2), screenSize.y-100-offset, texture,shader,white);
                count++;
            }
        } else if (openMenu == "shop") {
            gui.renderQuad(screenSize.x/2-(300/2), screenSize.y-350, 300, 300, texture, shader, blue);
            if (selectedTab == "pickaxes") {
                int count = 0;
                for (Pickaxe &pickaxe: pickaxeData) {
                    int offset = count*50;
                    gui.renderText(pickaxe.name/*+" level:"+ std::to_string(pickaxe.level) + " power:" + std::to_string(pickaxe.power)+ " cost:$" + std::to_string(pickaxe.cost)*/, screenSize.x/2-(300/2), screenSize.y-100-offset, texture,shader,white);
                    count++;
                }
            } else if (selectedTab == "backpacks") {
                int count = 0;
                for (Backpack &backpack: backpackData) {
                    int offset = count*50;
                    gui.renderText(backpack.name/*+" level:"+ std::to_string(pickaxe.level) + " power:" + std::to_string(pickaxe.power)+ " cost:$" + std::to_string(pickaxe.cost)*/, screenSize.x/2-(300/2), screenSize.y-100-offset, texture,shader,white);
                    count++;
                }
            }
        }
        
        for (Button &button: buttons) {
            auto it = visibleButtons.find(button.id);
            //checks if the iterator reaches the end of the map and then also requires the value to be true for visiblity
            bool buttonVisible = it != visibleButtons.end() && it -> second;
            if (buttonVisible) {
                gui.renderButton(button, texture, shader);
            }
        }
        
        mousePressed = false;
        
        glfwPollEvents();
        glfwSwapBuffers(window.ptr);
    }

    
    glfwTerminate();
}
