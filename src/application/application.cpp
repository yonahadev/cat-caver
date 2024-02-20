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

std::vector<TextureURL> urls = {
    {"/Users/tom/Documents/cplusplus/cat-caver/res/spritesheet.png",true},
    {"/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.png",false}
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
    
    Window window(screenSize,WINDOW_NAME);
    
    glfwGetWindowContentScale(window.ptr, &windowScale.x, &windowScale.y);
    
    glfwSetKeyCallback(window.ptr, handleKeypress);
    glfwSetWindowSizeCallback(window.ptr, resizeWindow);
    glfwSetMouseButtonCallback(window.ptr, handleMouseButton);
    
    Shader textShader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/textVertexShader.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/textFragmentShader.glsl");
    Shader terrainShader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/terrainVertexShader.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/textureFragmentShader.glsl");
    Shader spriteShader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/spriteVertexShader.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/textureFragmentShader.glsl");
    Shader quadShader("/Users/tom/Documents/cplusplus/cat-caver/src/shaders/quadVertexShader.glsl","/Users/tom/Documents/cplusplus/cat-caver/src/shaders/quadFragmentShader.glsl");

    Texture texture(urls);
    
    
    Player player(1,-2,playerSprite);
    player.generateGLQuad();
    
    NPC shopkeeper(1,-2,shopkeeperSprite);
    shopkeeper.generateGLQuad();
    
    Terrain terrain;
    
    Mat3 orthoMatrix = Mat3::Orthographic(
                                          (-aspectRatio.x/2)+0.5,
                                          (aspectRatio.x/2)+0.5,
                                          (-aspectRatio.y/2)+0.5,
                                          (aspectRatio.y/2)+0.5
                                          );
    
    GUI gui("/Users/tom/Documents/cplusplus/cat-caver/res/fontImg.fnt");
    
    Mouse mouse;
    mouse.vao.genArrays();
    mouse.vbo.genBuffer();

    std::vector<float> vertices;
    generateUIQuad(16, 10, (-aspectRatio.x/2)+0.5, (-aspectRatio.y/2)+0.5, vertices,1,false);
    VBO lightVBO;
    VAO lightVAO;
    lightVBO.genBuffer();
    lightVAO.genArrays();
    lightVAO.bindArray();
    lightVBO.bindBuffer();
    lightVBO.bindData(vertices,2);
    lightVAO.enableAttributes(2);
    lightVAO.unbindArray();
    
    float keyTime = glfwGetTime();
    
    mouse.currentTile = dirt;
    
    gui.setVisibleButtons({menuToggles});
    

    
    
    while (!glfwWindowShouldClose(window.ptr)) {
    
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        bool terrainUpdated = false;
        
        for (Tile &tile: terrain.tiles) {
            
            bool correctIndex = tile.blockIndex == coal;
            bool inTerrain = tile.coordinates.y != 0 && tile.coordinates.x != 0 && tile.coordinates.x != terrainWidth -1;
            
            if (correctIndex && inTerrain) {
                
                tile.accelerate(terrain.getRawBlockIndices());
                tile.collisions = {};
//                terrainUpdated = tile.collisions.empty();
                
                if (tile.airborne < -20) {
                    tile.falling = true;
                }
                
                
                if (tile.falling) {
                    int x = std::floor(tile.coordinates.x);
                    int y = std::floor(tile.coordinates.y);
                    if (tile.airborne == 0.0f) {
                        tile.falling = false;
//                        std::cout << "tile stopped falling: " << x << "," << y << "\n";
                        terrain.tiles[x+(-y*terrainWidth)] = Tile(x,y,tile.blockIndex);
                        terrain.tiles[x+((-y-1)*terrainWidth)] = Tile(x,y+1,dirt);
                    } else {
//                        std::cout << "falling block: " << x << "," << y << "\n";
                    }

                }//using value greater than the -2.5 subtraced per frame to check for actually falling tiles
            }
        }
        
        
        const int depth = int(abs(floor(player.coordinates.y)));

        if (depth > terrain.height-20) {
            terrain.generateLayer(depth);
            terrain.generateBuffer(depth);
        }
        
        if (abs(depth-terrain.generatedDepth) > 5 || terrainUpdated) {
            terrain.generateBuffer(depth);
        }
     
        const bool atSurface = depth <= 4;
        
        std::vector<Button> buttons = {}; //atm have to redefine per frame to account for changes to screen size
        buttons.emplace_back(menuToggles,"teleport",gui.getWidth("teleport"),40,50,screenSize.y-200,red,white,"");
        buttons.emplace_back(dialogueButton,"dialogue",screenSize.x+200,screenSize.y,-200,0,transparent,transparent,"");
        
//        buttons.emplace_back(menuToggles,"ores",gui.getWidth("ores"),40,50,screenSize.y-250,green,white,"");
//        buttons.emplace_back(menuToggles,"progress",gui.getWidth("progress"),40,50,screenSize.y-300,grey,white,"");
        
        int menuWidth = screenSize.x*(0.75);
        int menuHeight = screenSize.y*(0.75);
        int menuY = screenSize.y/2-(menuHeight/2);
        int menuX = screenSize.x/2-(menuWidth/2);
        
        const int pickaxeButtonWidth = gui.getWidth("pickaxes");
        const int backpackButtonWidth = gui.getWidth("backpacks");
        
        buttons.emplace_back(tabSelector,"backpacks",gui.getWidth("backpacks"),30,screenSize.x/2-(300/2)+pickaxeButtonWidth+20,screenSize.y-400,red,white,"");
        buttons.emplace_back(tabSelector,"pickaxes",pickaxeButtonWidth,30,screenSize.x/2-(300/2),screenSize.y-400,red,white,"");
        buttons.emplace_back(tabSelector,"sell",gui.getWidth("sell"),30,screenSize.x/2-(300/2)+pickaxeButtonWidth+backpackButtonWidth+40,screenSize.y-400,red,white,"");
        
        buttons.emplace_back(teleport,"surface",gui.getWidth("surface"),40,menuX+200,menuHeight-50,red,white,"");
        buttons.emplace_back(teleport,"mine",gui.getWidth("mine"),40,menuX+400,menuHeight-50,red,white,"");
        
        buttons.emplace_back(closeButton,"X",25,25,menuX+menuWidth-25,menuY+menuHeight-25,red,white,"");
        
        int count = 0;
        for (const Pickaxe &pickaxe: pickaxeData) {
            int offset = count*50;
            auto it = player.ownedPickaxes.find(pickaxe);
            bool owned = it != player.ownedPickaxes.end();
            if (owned) {
                if (player.equippedPickaxe == pickaxe) {
                    int width = gui.getWidth("equipped");
                    buttons.emplace_back(pickaxeEquip,"equipped",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,grey,white,std::to_string(count));
                } else {
                    int width = gui.getWidth("equip");
                    buttons.emplace_back(pickaxeEquip,"equip",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,blue,white,std::to_string(count));
                }
            } else {
                std::string text = "$"+std::to_string(pickaxe.cost);
                int width = gui.getWidth(text);
                buttons.emplace_back(pickaxeEquip,text,width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,green,white,std::to_string(count));
                    
            }

            count++;
        }
        count = 0;
        for (const Backpack &backpack: backpackData) {
            const int offset = count*50;
            if (player.ownedBackpacks[backpack]) {
                if (player.equippedBackpack == backpack) {
                    const int width = gui.getWidth("equipped");
                    buttons.emplace_back(backpackEquip,"equipped",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,grey,white,std::to_string(count));
                } else {
                    const int width = gui.getWidth("equip");
                    buttons.emplace_back(backpackEquip,"equip",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,blue,white,std::to_string(count));
                }
            } else {
                std::string text = "$"+std::to_string(backpack.cost);
                const int width = gui.getWidth(text);
                buttons.emplace_back(backpackEquip,text,width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,green,white,std::to_string(count));
                    
            }

            count++;
        }
        
        count = 0;
        
        for (auto &[block,value]: player.blockCounts) {
            int offset = count*50;
            int width = gui.getWidth("sell");
            if (value > 0) {
                buttons.emplace_back(oreSell,"sell",gui.getWidth("sell"),30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,green,white,std::to_string(block.textureIndex));
                count++;
                
            }
        }
        
        count = 0;
        for (int i = 0; i < static_cast<int>(worldData.size()); i++) {
            
            World world = worldData[i];
            const int offset = count*50;
            bool worldOwned = false;
            for (std::string &worldName: player.ownedWorlds) {
                if(worldName == world.name) {
                    worldOwned = true;
                }
            }
            if (worldOwned) {
                if (terrain.currentWorld == i) {
                    const int width = gui.getWidth("equipped");
                    buttons.emplace_back(worldSelect,"equipped",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,grey,white,std::to_string(count));
                } else {
                    const int width = gui.getWidth("equip");
                    buttons.emplace_back(worldSelect,"equip",width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,blue,white,std::to_string(count));
                }
            } else {
//                std::string text = "$"+std::to_string(world.cost);
//                const int width = gui.getWidth(text);
//                buttons.emplace_back(worldSelect,text,width,30,screenSize.x/2+(300/2)-width,screenSize.y-100-offset,green,white,std::to_string(count));
                    
            }

            count++;
        }

        

        
        texture.setTexture("spritesheet",true);
        
        spriteShader.bind();
        spriteShader.loadUniform<Mat3>(orthoMatrix*player.matrix,"u_Transformation");
        
        terrain.backgroundVAO.bindArray();
        
        terrain.backgroundVBO.draw();
        
        terrainShader.bind();
  
        
        terrainShader.loadUniform<Mat3>(orthoMatrix*player.matrix, "u_Transformation");
        
        terrain.vao.bindArray();
        
        glDrawArraysInstanced(GL_TRIANGLES,0,6,terrain.instanceCount);
        

        
        quadShader.bind();
        quadShader.loadUniform<Mat3>(orthoMatrix*player.matrix,"u_Transformation");
        
        if (terrain.path.empty() == false) {
            quadShader.loadUniform<Vec4f>(colourVector[red], "u_QuadColour");
            terrain.pathVAO.bindArray();
            terrain.pathVBO.draw();
            quadShader.loadUniform<Vec4f>(colourVector[white], "u_QuadColour");
        }
        
        spriteShader.bind();
        spriteShader.loadUniform<Mat3>(orthoMatrix*player.matrix*shopkeeper.matrix,"u_Transformation");
        shopkeeper.vao.bindArray();
        shopkeeper.vbo.draw();
        shopkeeper.accelerate(terrain.getRawBlockIndices());
        shopkeeper.collisions = {};
        const int shopkeeperX = static_cast<int>(round(shopkeeper.coordinates.x));
        const int shopkeeperY = static_cast<int>(round(shopkeeper.coordinates.y));
                
        spriteShader.loadUniform<Mat3>(orthoMatrix,"u_Transformation");
        player.vao.bindArray();
        player.vbo.draw();
        
        mouse.generateBuffer();
        if (mouse.vbo.verticesCount > 0) {
            quadShader.loadUniform<Mat3>(orthoMatrix*player.matrix,"u_Transformation");
            quadShader.loadUniform<int>(false, "u_IsTexture");
            if (mouse.backpackFull && mouse.holding > 0) {
                quadShader.loadUniform<Vec4f>(colourVector[red], "u_QuadColour");
                gui.errorMessage = "Backpack full";
                gui.errorTimeSet = glfwGetTime();
                gui.errorDuration = 2;
            } else if (mouse.validPickaxeLevel == false && mouse.holding > 0) {
                quadShader.loadUniform<Vec4f>(colourVector[red], "u_QuadColour");
                gui.errorMessage = "Please upgrade your pickaxe";
                gui.errorTimeSet = glfwGetTime();
                gui.errorDuration = 2;
            } else {
                quadShader.loadUniform<Vec4f>(colourVector[green], "u_QuadColour");
            }
            mouse.vao.bindArray();
            mouse.vbo.draw();
        }
        
        handleMouseMove(window.ptr, screenSize, aspectRatio,terrain,mouse,player);
        if (gui.inDialogue == false) {
            handleMining(window.ptr,terrain,mouse,player,gui);
            handleKeyPress(window.ptr,player,terrain,keyTime);
        }
        
        quadShader.bind();
        
        if (lightingOn) {
//            
//            std::cout << "Outputting light" << "\n";
            
            Vec2f size = {static_cast<float>(screenSize.x*windowScale.x),static_cast<float>(screenSize.y*windowScale.y)};
            
            int lightRadius = screenSize.x/3;
            if (depth < 5) {
                lightRadius = screenSize.x;
            }
            quadShader.loadUniform<Vec2f>(size, "u_ScreenSize");
            
            quadShader.loadUniform<int>(lightRadius, "u_LightRadius");
            quadShader.loadUniform<Mat3>(orthoMatrix, "u_Transformation");
            quadShader.loadUniform<Vec4f>(colourVector[white], "u_QuadColour");
            
            lightVAO.bindArray();
            lightVBO.draw();
            quadShader.loadUniform<int>(0, "u_LightRadius");
        }
        
        textShader.loadUniform<Mat3>(guiMatrix, "u_Transformation");
        spriteShader.loadUniform<Mat3>(guiMatrix, "u_Transformation");
        quadShader.loadUniform<Mat3>(guiMatrix, "u_Transformation");

         
        const int time = static_cast<int>(glfwGetTime());
        std::string timeString = "Time: " + std::to_string(time);
        const int width = gui.getWidth(timeString);
        
        bool interactionTriggered = false;
        
        if (gui.openMenu == "") {
            int playerX = round(player.coordinates.x);
            int playerY = round(player.coordinates.y);
            
            std::vector<Vec2i> neighbours = terrain.getNeighbours(playerX,playerY,true);
            
            bool validPosition = false;
            
            for (Vec2i &block: neighbours) {
                if (shopkeeperX == block.x && shopkeeperY == block.y) {
                    validPosition = true;
                }
            }
            
            const bool validMouse = mouse.tileX == shopkeeperX  && mouse.tileY == shopkeeperY;
            
            std::cout << shopkeeper.coordinates.x << "," << shopkeeper.coordinates.y << "\n";
            std::cout << mouse.tileX << "," << mouse.tileY << "\n";
            
            
            if (mousePressed && validMouse && validPosition && gui.inDialogue == false) {
                gui.setVisibleButtons({dialogueButton});
                gui.dialogue.setDialogue(0);
                interactionTriggered = true;
            }
            
            Quest quest = player.currentQuest;
            std::string questTitle = quest.title;
            int questTitleWidth = gui.getWidth(questTitle);
            gui.renderText("Current Quest:", screenSize.x-questTitleWidth-50, screenSize.y-150, texture, textShader, white, false, 1);
            
            gui.renderText(questTitle, screenSize.x-questTitleWidth-50, screenSize.y-200, texture, textShader, white, false, 1);
            gui.renderText(questTitle, screenSize.x-questTitleWidth-50, screenSize.y-200, texture, textShader, white, false, 1);
            int multilineOffset = gui.renderText(quest.description, screenSize.x-questTitleWidth-50, screenSize.y-250, texture, textShader, grey, true, questTitleWidth);
            count = 0;
            for (const auto &[ore,requirement]: quest.blockRequirements) {
                Block block = blockData[ore];
                gui.renderQuad(screenSize.x-questTitleWidth-50-55, screenSize.y-312-count-multilineOffset, 50, 50, texture, spriteShader, white, true, ore);
                gui.renderText(std::to_string(player.blockCounts[block])+"/"+std::to_string(requirement), screenSize.x-questTitleWidth-50, screenSize.y-300-count-multilineOffset, texture, textShader,white,false,-1);
                count += 50;
            }
            if (player.money < quest.moneyRequirement) {
                gui.renderText("$" + std::to_string(player.money)+ "/"+std::to_string(quest.moneyRequirement), screenSize.x-questTitleWidth-50, screenSize.y-250-multilineOffset, texture, textShader, red,false,-1);
            } else {
                gui.renderText("$" + std::to_string(player.money)+ "/"+std::to_string(quest.moneyRequirement), screenSize.x-questTitleWidth-50, screenSize.y-250-multilineOffset, texture, textShader, green,false,-1);
            }
            
            gui.renderText(timeString, screenSize.x-width-50, screenSize.y-50, texture,textShader,white,false,-1);
            gui.renderText("Depth: " + std::to_string(depth), 50, screenSize.y-50, texture,textShader,white,false,-1);
            if (player.backpackCount >= player.equippedBackpack.capacity) {
                gui.renderText("Backpack: " + std::to_string(player.backpackCount)+"/"+std::to_string(player.equippedBackpack.capacity), 50, screenSize.y-100, texture, textShader, red,false,-1);
            } else {
                gui.renderText("Backpack: " + std::to_string(player.backpackCount)+"/"+std::to_string(player.equippedBackpack.capacity), 50, screenSize.y-100, texture, textShader, white,false,-1);
            }
            gui.renderText("$" + std::to_string(player.money), 50, screenSize.y-150, texture, textShader, green,false,-1);
            if (mouse.currentTile != -1) {
                Block currentBlock = blockData[mouse.currentTile];
                int width = gui.getWidth(currentBlock.name);
                if (player.equippedPickaxe.level >= currentBlock.level) {
                    gui.renderQuad(screenSize.x-width-75, screenSize.y-112, 50, 50, texture, spriteShader, white, true, mouse.currentTile);
                    gui.renderText(blockData[mouse.currentTile].name, screenSize.x-width-25, screenSize.y-100, texture, textShader, white, false, 0);
                } else {
                    gui.renderQuad(screenSize.x-width-85, screenSize.y-112, 50, 50, texture, spriteShader, grey, true, mouse.currentTile);
                    gui.renderText(blockData[mouse.currentTile].name, screenSize.x-width-25, screenSize.y-100, texture, textShader, red, false, 0);
                }
            }
            
            if (gui.inDialogue == false && glfwGetTime() - gui.rewardTimeSet < gui.rewardDuration) {
                int width = gui.getWidth(gui.rewardMessage);
                int maxWidth = screenSize.x*(0.5);
                if (width > maxWidth) {
                    gui.renderText(gui.rewardMessage, screenSize.x*(0.25), screenSize.y*(0.4), texture, textShader, white, true, screenSize.x*(0.5));
                } else {
                    gui.renderText(gui.rewardMessage, screenSize.x*(0.5)-width*(0.5), screenSize.y*(0.4), texture, textShader, white, false, screenSize.x*(0.5));
                }
                int count = 1;
                for (auto &[block,blockCount]: gui.rewards) {
                    int y = screenSize.y*(0.4)-count*60;
                    gui.renderQuad(screenSize.x*(0.25), y, 50, 50, texture, spriteShader, white, true, block.textureIndex);
                    gui.renderText(std::to_string(blockCount), screenSize.x*(0.25)+60,y, texture, textShader, green, false, 0);
                    count++;
                }
            }
            
            if (gui.errorDuration != 0 && gui.inDialogue == false) {
                if (glfwGetTime() - gui.errorTimeSet < gui.errorDuration) {
                    int width = gui.getWidth(gui.errorMessage);
                    int maxWidth = screenSize.x*(0.5);
                    if (width > maxWidth) {
                        gui.renderText(gui.errorMessage, screenSize.x*(0.25), screenSize.y*(0.25), texture, textShader, red, true, screenSize.x*(0.5));
                    } else {
                        gui.renderText(gui.errorMessage, screenSize.x*(0.5)-width*(0.5), screenSize.y*(0.25), texture, textShader, red, false, screenSize.x*(0.5));
                    }
                }
            }
        }
        
        if (gui.openMenu == "ores") {
            gui.renderQuad(menuX, menuY, menuWidth, menuHeight, texture, quadShader, blue,false,1);
            int count = 0;
            for (auto &[block,value]: player.blockCounts) {
                int offset = count*50;
                gui.renderText(block.name+ ": " + std::to_string(value), menuX, screenSize.y-100-offset, texture,textShader,white,false,-1);
                count++;
            }
        }
        if (gui.openMenu == "teleport") {
            gui.renderQuad(menuX, menuY, menuWidth, menuHeight, texture, quadShader, grey,false,1);
            gui.renderText("Teleport", menuX, menuHeight, texture, textShader, white, -1, 0);
            int count = 0;
            for (const World &world: worldData) {
                bool owned = false;
                for (std::string &worldName: player.ownedWorlds){
                    if (worldName == world.name) {
                        owned = true;
                    }
                }
                int textColour = red;
                if (owned) {
                    textColour = white;
                }
                gui.renderText(world.name, menuX+50+count*300, menuHeight-100, texture, textShader, textColour, false, -1);
                count++;
            }
 
        } else if (gui.openMenu == "shop") {
            gui.renderText("$" + std::to_string(player.money), 50, screenSize.y-50, texture, textShader, green,false,-1);
            gui.renderQuad(menuX, menuY, menuWidth, menuHeight, texture, quadShader, blue, false,1);
            if (gui.selectedTab == "pickaxes") {
                int count = 0;
                for (const Pickaxe &pickaxe: pickaxeData) {
                    int offset = count*100;
                    gui.renderText(pickaxe.name/*+" level:"+ std::to_string(pickaxe.level) + " power:" + std::to_string(pickaxe.power)+ " cost:$" + std::to_string(pickaxe.cost)*/, menuX, screenSize.y-50-offset, texture,textShader,white,false,-1);
                    gui.renderText("level:"+ std::to_string(pickaxe.level), menuX, screenSize.y-100-offset, texture,textShader,white,false,-1);
                    count++;
                }
            } else if (gui.selectedTab == "backpacks") {
                int count = 0;
                for (const Backpack &backpack: backpackData) {
                    int offset = count*100;
                    gui.renderText(backpack.name/*+" level:"+ std::to_string(pickaxe.level) + " power:" + std::to_string(pickaxe.power)+ " cost:$" + std::to_string(pickaxe.cost)*/, menuX, screenSize.y-50-offset, texture,textShader,white,false,-1);
                    gui.renderText("capacity:"+ std::to_string(backpack.capacity), menuX, screenSize.y-100-offset, texture,textShader,white,false,-1);
                    count++;
                }
            } else if (gui.selectedTab == "sell") {
                int count = 0;
                for (auto &[block,value]: player.blockCounts) {
                    int offset = count*50;
                    int xOffset = 0;
                    if (value > 0) {
                        gui.renderText(std::to_string(value), menuX+xOffset, screenSize.y-100-offset, texture,textShader,white,false,-1);
                        xOffset += 25;
                        gui.renderQuad(menuX+xOffset, screenSize.y-100-offset, 25, 25, texture, spriteShader, white, true, block.textureIndex);
                        xOffset += 25;
                        gui.renderText(block.name, menuX+xOffset, screenSize.y-100-offset, texture,textShader,white,false,-1);
                        xOffset += gui.getWidth(block.name) + 25;
                        gui.renderText("$"+std::to_string(block.sellValue), menuX+25+xOffset, screenSize.y-100-offset, texture,textShader,green,false,-1);
                        count++;
                    }
                }
            }
        }
        
        if (gui.inDialogue) {
            gui.renderQuad(0,25, 200, 200, texture, spriteShader, white, true, shopkeeperSprite);
            gui.renderQuad(200, 25, screenSize.x*(0.75), screenSize.y*(0.25), texture, quadShader, red, false, 1);
            
            int lineIndex = gui.dialogue.currentLine;
            if (lineIndex < gui.dialogue.lineCount) {
                gui.setVisibleButtons({dialogueButton});
                std::string currentLine = gui.dialogue.currentNode.dialogue[gui.dialogue.currentLine];
                gui.renderText(currentLine, 225, screenSize.y*(0.25)-25, texture, textShader, white,true,screenSize.x*(0.75)-75);
            } else {
                gui.setVisibleButtons({dialogueChoice});
                int count = 0;
                for (Choice &choice: gui.dialogue.currentNode.choices) {
                    std::string currentLine = choice.choiceText;
                    int width = gui.getWidth(currentLine);
                    
                    buttons.emplace_back(dialogueChoice,currentLine,width,35,225,screenSize.y*(0.25)-25-count,grey,white,choice.nextNode);
                    count += 50;
                }
            }
            
        }
        
        
        
        
        for (Button &button: buttons) {
            auto it = gui.visibleButtons.find(button.id);
            const bool buttonVisible = it != gui.visibleButtons.end() && it -> second;
            if (buttonVisible) {
                gui.renderButton(button, texture, quadShader,textShader);
            }
        }
        

        handleGUI(window.ptr, terrain, mouse, player, buttons, screenSize, mousePressed, gui, atSurface);
        
        if (interactionTriggered) {
            gui.inDialogue = true;
        }
        
        mousePressed = false;
        
        glfwPollEvents();
        glfwSwapBuffers(window.ptr);
    }

    
    glfwTerminate();
}
