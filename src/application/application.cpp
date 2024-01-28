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
#include "vertex.hpp"
#include <vector>
#include <string>
#include "input.hpp"
#include "mouse.hpp"
#include "vec2.hpp"
#include "vec4.hpp"
#include "text.hpp"
#include <fstream>
#include <unordered_map>
#include "block.hpp"
#include "quad.hpp"
#include "gui.hpp"
#include "button.hpp"
#include "pickaxe.hpp"
#include "backpack.hpp"
#include "PerlinNoise.hpp"
#include "NPC.hpp"
#include "constants.hpp"

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

/// <#Description#>
void runApplication() {
    
    Window window(screenSize,WINDOW_NAME);
    
    glfwGetWindowContentScale(window.ptr, &windowScale.x, &windowScale.y);
    
    glfwSetKeyCallback(window.ptr, handleKeypress);
    glfwSetWindowSizeCallback(window.ptr, resizeWindow);
    glfwSetMouseButtonCallback(window.ptr, handleMouseButton);
    
    Shader shader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/vertex.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/fragment.glsl");
    Shader terrainShader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/terrainVertexShader.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/terrainFragmentShader.glsl");
    Texture texture(urls);
    
    
    Player player(1,-2,8);
    player.generateGLQuad();
    
    NPC shopkeeper(1,-2,9);
    shopkeeper.generateGLQuad();
    
    Terrain terrain;
    
    Mat3 orthoMatrix = Mat3::Orthographic(
                                          (-aspectRatio.x/2)+0.5,
                                          (aspectRatio.x/2)+0.5,
                                          (-aspectRatio.y/2)+0.5,
                                          (aspectRatio.y/2)+0.5
                                          );
    
    Gui gui("/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.fnt");
    
    Mouse mouse;
    mouse.vao.genArrays();
    mouse.vbo.genBuffer();

    std::vector<Vertex> vertices;
    generateUIQuad(16, 10, (-aspectRatio.x/2)+0.5, (-aspectRatio.y/2)+0.5, vertices,1);
    VBO lightVBO;
    VAO lightVAO;
    lightVBO.genBuffer();
    lightVAO.genArrays();
    lightVAO.bindArray();
    lightVBO.bindBuffer();
    lightVBO.bindData(vertices);
    lightVAO.enableAttributes();
    lightVAO.unbindArray();
    
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
        
//        for (Tile &tile: terrain.tiles) {
//            
//            bool correctIndex = tile.blockIndex != 3;
//            bool inTerrain = tile.coordinates.y != 0 && tile.coordinates.x != 0 && tile.coordinates.x != terrain.config.width -1;
//            
//            if (correctIndex && inTerrain) {
//                
//                tile.accelerate(terrain.getRawBlockIndices());
//                tile.collisions = {};
//                terrain.updated = tile.collisions.empty();
//                
//                if (tile.airborne < -15) {
//                    tile.falling = true;
//                }
//                
//                
//                if (tile.falling) {
//                    int x = std::floor(tile.coordinates.x);
//                    int y = std::floor(tile.coordinates.y);
//                    if (tile.airborne == 0.0f) {
//                        tile.falling = false;
////                        std::cout << "tile stopped falling: " << x << "," << y << "\n";
//                        terrain.tiles[x+(-y*terrain.config.width)] = Tile(x,y,tile.blockIndex);
//                        terrain.tiles[x+((-y-1)*terrain.config.width)] = Tile(x,y+1,3);
//                    } else {
////                        std::cout << "falling block: " << x << "," << y << "\n";
//                    }
//
//                }//using value greater than the -2.5 subtraced per frame to check for actually falling tiles
//            }
//        }
        
        
        const int depth = int(abs(floor(player.coordinates.y)));

        if (depth > terrain.height-20) {
            terrain.generateLayer(depth);
            terrain.generateBuffer(depth);
        }
     
        const bool atSurface = depth <= 4;
        
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
        
        
        const int pickaxeButtonWidth = gui.getWidth("pickaxes");
        buttons.emplace_back(3,"backpacks",gui.getWidth("backpacks"),30,screenSize.x/2-(300/2)+pickaxeButtonWidth+20,screenSize.y-400,red,white,"");
        buttons.emplace_back(3,"pickaxes",pickaxeButtonWidth,30,screenSize.x/2-(300/2),screenSize.y-400,red,white,"");
        
        int count = 0;
        for (const Pickaxe &pickaxe: pickaxeData) {
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
        for (const Backpack &backpack: backpackData) {
            const int offset = count*50;
            if (player.ownedBackpacks[backpack]) {
                if (player.equippedBackpack == backpack) {
                    const int width = gui.getWidth("equipped");
                    buttons.emplace_back(5,"equipped",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,grey,white,std::to_string(count));
                } else {
                    const int width = gui.getWidth("equip");
                    buttons.emplace_back(5,"equip",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,blue,white,std::to_string(count));
                }
            } else {
                std::string text = "$"+std::to_string(backpack.cost);
                const int width = gui.getWidth(text);
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
        
        terrain.backgroundVAO.bindArray();
        terrain.backgroundVBO.draw();
  
        terrainShader.bind();
        
        terrainShader.loadUniform<Mat3>(orthoMatrix*player.matrix, "u_Transformation");
        
        terrain.vao.bindArray();
        
        glDrawArraysInstanced(GL_TRIANGLES,0,6,terrain.instanceCount);
        
        shader.bind();
        

        
        shader.loadUniform<Mat3>(orthoMatrix*player.matrix*shopkeeper.matrix,"u_Transformation");
        shopkeeper.vao.bindArray();
        shopkeeper.vbo.draw();
        shopkeeper.accelerate(terrain.getRawBlockIndices());
        shopkeeper.collisions = {};
        const int shopkeeperX = static_cast<int>(shopkeeper.coordinates.x);
        const int shopkeeperY = static_cast<int>(shopkeeper.coordinates.y);
        
        const bool valid = mouse.tileX == shopkeeperX  && mouse.tileY == shopkeeperY;
        
    //        player.coordinates.print();
    //        shopkeeper.coordinates.print();
        
        if (mousePressed && valid) {
            std::cout << "shopkeeper interaction triggered" << "\n";
            openMenu = "shop";
            selectedTab = "pickaxes";
            visibleButtons[3] = true;
            visibleButtons[4] = true;
        }
        
        shader.loadUniform<int>(true, "u_IsTexture");
        shader.loadUniform<Mat3>(orthoMatrix,"u_Transformation");
        player.vao.bindArray();
        player.vbo.draw();
        
        mouse.generateBuffer();
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
        
        shader.loadUniform<Mat3>(guiMatrix, "u_Transformation");
        
        
        const int time = static_cast<int>(glfwGetTime());
        std::string timeString = "Time: " + std::to_string(time);
        const int width = gui.getWidth(timeString);
        
        gui.renderText(timeString, screenSize.x-width-50, screenSize.y-50, texture,shader,white);
        gui.renderText("Depth: " + std::to_string(depth), 50, screenSize.y-50, texture,shader,white);
        gui.renderText("Backpack: " + std::to_string(player.backpackCount)+"/"+std::to_string(player.equippedBackpack.capacity), 50, screenSize.y-100, texture, shader, white);
        gui.renderText("$" + std::to_string(player.money), 50, screenSize.y-150, texture, shader, green);
        
        if (openMenu == "ores") {
            gui.renderQuad(screenSize.x/2-(300/2), screenSize.y-350, 300, 300, texture, shader, blue,false,1);
            int count = 0;
            for (auto &[block,value]: player.blockCounts) {
                int offset = count*50;
                gui.renderText(block.name+ ": " + std::to_string(value), screenSize.x/2-(300/2), screenSize.y-100-offset, texture,shader,white);
                count++;
            }
        } else if (openMenu == "shop") {
            gui.renderQuad(screenSize.x/2-(300/2), screenSize.y-350, 300, 300, texture, shader, blue,false,1);
            if (selectedTab == "pickaxes") {
                int count = 0;
                for (const Pickaxe &pickaxe: pickaxeData) {
                    int offset = count*50;
                    gui.renderText(pickaxe.name/*+" level:"+ std::to_string(pickaxe.level) + " power:" + std::to_string(pickaxe.power)+ " cost:$" + std::to_string(pickaxe.cost)*/, screenSize.x/2-(300/2), screenSize.y-100-offset, texture,shader,white);
                    count++;
                }
            } else if (selectedTab == "backpacks") {
                int count = 0;
                for (const Backpack &backpack: backpackData) {
                    int offset = count*50;
                    gui.renderText(backpack.name/*+" level:"+ std::to_string(pickaxe.level) + " power:" + std::to_string(pickaxe.power)+ " cost:$" + std::to_string(pickaxe.cost)*/, screenSize.x/2-(300/2), screenSize.y-100-offset, texture,shader,white);
                    count++;
                }
            }
        }
        
        gui.renderQuad(0, 0, 400, 400, texture, shader, white, true, 9);
        
        for (Button &button: buttons) {
            auto it = visibleButtons.find(button.id);
            //checks if the iterator reaches the end of the map and then also requires the value to be true for visiblity
            const bool buttonVisible = it != visibleButtons.end() && it -> second;
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
