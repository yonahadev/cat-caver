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
#include "quad.hpp"

void handleMouseMove(GLFWwindow* window,const Vec2f &pos,const Vec2i &screenSize,const Vec2i &aspectRatio,const Terrain &terrain, Mouse &mouse, const Player &player) {
    
    glfwGetCursorPos(window, &mouse.screenX, &mouse.screenY);
    double mouseX = mouse.screenX;
    double mouseY = mouse.screenY;
    
//    if (mouseX > screenSize.x || mouseX < 0 || mouseY > screenSize.y || mouseY < 0 ) return 0;
    
    float xMultiplier = screenSize.x/aspectRatio.x;
    float yMultiplier = screenSize.y/aspectRatio.y;

    mouseX *= 1/xMultiplier;
    mouseY *= 1/yMultiplier;
    
    mouseX -= aspectRatio.x*0.5;
    mouseY -= aspectRatio.y*0.5;
    
    mouseY *=  -1;
    
    mouseX += pos.x;
    mouseY += pos.y;
    
    mouseX += 0.5;
    mouseY += 0.5;
    
    
//    std::cout << "Mouse coordinates: " << mouseX << "," << mouseY << "\n";
    
    int newX = floor(mouseX);
    int newY = floor(mouseY);
    
    if (newX != mouse.tileX || newY != mouse.tileY) {
        mouse.holding = 0;
    }
    
    mouse.tileX = newX;
    mouse.tileY = newY;
    
    //    std::cout << "Tile coordinates: " << mouse.tileX << "," << mouse.tileY << "\n";
//    bool mouseInXBoundary = mouse.tileX > 0 && mouse.tileX < terrain.config.width-1;
//    bool mouseInYBoundary = -mouse.tileY < terrain.height && -mouse.tileY > 0;
    
    int playerX = round(player.coordinates.x);
    int playerY = round(player.coordinates.y);
    
    std::vector<Vec2i> neighbours = terrain.getNeighbours(playerX, playerY);
    
    bool isMineable = false;
    for (Vec2i &block: neighbours) {
        if (mouse.tileX == block.x && mouse.tileY == block.y) {
            isMineable = true;
        }
    }
    
    if (isMineable) {
        mouse.currentTile  = terrain.getTile(mouse.tileX, mouse.tileY);
    } else {
        mouse.currentTile = -1;
    }
    
}

void handleMining(GLFWwindow* window,Terrain &terrain, Mouse &mouse, Player &player) {

    if (mouse.currentTile == -1) return;
    
    Block block = terrain.blockData[mouse.currentTile];
    
    mouse.backpackFull = player.backpackCount >= player.equippedBackpack.capacity;
    
    bool isMineable = block.level != -1;
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && isMineable) {
        
        
        mouse.holding += 16.6667 + player.equippedPickaxe.power*2;
        
        int blockHealth = block.hp;
        
        
        if (mouse.holding > blockHealth && mouse.backpackFull == false) {
            terrain.mineBlock(mouse.tileX, mouse.tileY);
            std::string blockName = block.name;
            if (block.name != "special") {
                player.blockCounts[block] += 1;
                player.backpackCount += 1;
            } else {
//                std::cout << "mined special block" << "\n";
                std::vector<Block> minedBlocks = terrain.triggerExplosion(mouse.tileX, mouse.tileY);
                for (auto &block: minedBlocks) {
                    player.blockCounts[block] += 1;
                    player.backpackCount += 1;
                }
            }
            mouse.holding = 0;
            terrain.generateBuffer();
        }
        mouse.minedPercentage = (mouse.holding/blockHealth)*100;
//        std::cout << "holding mouse button for: " << mouse.holding << "ms \n";
    } else {
        mouse.holding = 0;
    }
}

void handleGUI(GLFWwindow* window,Terrain &terrain, Mouse &mouse, Player &player, const std::vector<Button> &buttons,const Vec2i &screenSize, std::string &openMenu,std::string &selectedTab, bool mousePressed,const std::vector<Pickaxe> &pickaxeData, const std::vector<Backpack> &backpackData,std::unordered_map<int, bool> &visibleButtons, const bool atSurface) {

    if (mousePressed == false) return;
    
        float mouseY = screenSize.y-mouse.screenY;
        for (const auto &button: buttons) {
            
                bool validX = mouse.screenX >= button.x && mouse.screenX <= button.x+button.width;
                bool validY = mouseY >= button.y && mouseY <= button.y+button.height;
                auto it = visibleButtons.find(button.id);
                bool visible = it != visibleButtons.end() && it->second;
                if (validX && validY && visible) {
                    std::cout << button.text << " id:" << button.id << "\n";
                    switch(button.id) {
                        case 0: {
                            player.teleport(1, -3, terrain);
                            break;
                        }
                        case 1: {
                            if (atSurface == false) break;
                            player.backpackCount = 0;
                            for (auto &[block,count]: player.blockCounts) {
                                int totalValue = count*block.sellValue;
                                player.money += totalValue;
                                player.blockCounts[block] = 0;
                            }
                            break;
                        }
                        case 2: {
                            if (atSurface == false) break;
                            if (openMenu == button.text) {
                                openMenu = "";
                                selectedTab = "pickaxes";
                                visibleButtons[3] = false;
                                visibleButtons[4] = false;
                                visibleButtons[5] = false;
                            } else {
                                openMenu = button.text;
                                if (button.text == "shop") {
                                    if (atSurface) {
                                        visibleButtons[3] = true;
                                        visibleButtons[4] = true;
                                    } else {
                                        openMenu = "";
                                    }
                                }
                            }   
                            break;
                        }
                        case 3: {
                            selectedTab = button.text;
                            std::cout << "Selected tab: " << selectedTab << "\n";
                            if (selectedTab == "backpacks") {
                                visibleButtons[4] = false;
                                visibleButtons[5] = true;

                            } else if (selectedTab == "pickaxes") {
                                
                                visibleButtons[4] = true;
                                visibleButtons[5] = false;
                            }
                            break;
                        }
                        case 4: {
                            int itemIndex = std::stoi(button.metaInfo);
                            Pickaxe pickaxe = pickaxeData[itemIndex];
                            if (button.text == "equip") {
                                player.equippedPickaxe = pickaxe;
                                std::cout << "Equipped" << pickaxe.name << "\n";
                            } else if (player.money >= pickaxe.cost) {
                                player.equippedPickaxe = pickaxe;
                                player.ownedPickaxes[pickaxe] = true;
                                std::cout << "Equipped" << pickaxe.name << "\n";
                                player.money -= pickaxe.cost;
                            }
                            break;
                        }
                        case 5: {
                            int itemIndex = std::stoi(button.metaInfo);
                            Backpack backpack = backpackData[itemIndex];
                            if (button.text == "equip") {
                                player.equippedBackpack = backpack;
                                std::cout << "Equipped" << backpack.name << "\n";
                            } else if (player.money >= backpack.cost) {
                                std::cout << "Equipped" << backpack.name << "\n";
                                player.equippedBackpack = backpack;
                                player.ownedBackpacks[backpack] = true;
                                player.money -= backpack.cost;
                            }
                            break;
                        }
                            }
                    
                    }
            }
        }

void handleKeyPress(GLFWwindow *window, Player &player, const Terrain &terrain, float &time) {
    
    float jumpDelay = 0.25f;
    float moveSpeed = 0.03f;
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
       player.moveSprite(-moveSpeed,0,terrain);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            float currentTime = glfwGetTime();
            if (currentTime - time > jumpDelay ) {
                player.jump(terrain);
                time = currentTime;
            }
        }
   } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
       player.moveSprite(moveSpeed,0,terrain);
       if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
           float currentTime = glfwGetTime();
           if (currentTime - time > jumpDelay ) {
               player.jump(terrain);
               time = currentTime;
           }
       }
   } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
       float currentTime = glfwGetTime();
       if (currentTime - time > jumpDelay ) {
           player.jump(terrain);
           time = currentTime;
       }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
           player.moveSprite(-moveSpeed,0,terrain);
            
            
       } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
           player.moveSprite(moveSpeed,0,terrain);
       }
    }
    
    player.accelerate(terrain);
    
    player.collisions = {};
}
        

    
