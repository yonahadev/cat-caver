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
#include "constants.hpp"

void handleMouseMove(GLFWwindow* window,const Vec2i &screenSize,const Vec2i &aspectRatio,const Terrain &terrain, Mouse &mouse, const Player &player) {
    
    
    
    glfwGetCursorPos(window, &mouse.screenX, &mouse.screenY);
    double mouseX = mouse.screenX;
    double mouseY = mouse.screenY;
    
    float xMultiplier = screenSize.x/aspectRatio.x;
    float yMultiplier = screenSize.y/aspectRatio.y;

    mouseX *= 1/xMultiplier;
    mouseY *= 1/yMultiplier;
    
    mouseX -= aspectRatio.x*0.5;
    mouseY -= aspectRatio.y*0.5;
    
    mouseY *=  -1;
    
    mouseX += player.coordinates.x;
    mouseY += player.coordinates.y;
    
    mouseX += 0.5;
    mouseY += 0.5;
    
    
    int newX = floor(mouseX);
    int newY = floor(mouseY);
    
    if (newX != mouse.tileX || newY != mouse.tileY) {
        mouse.holding = 0;
    }
    
    mouse.tileX = newX;
    mouse.tileY = newY;
    
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
//        std::cout << "current tile: " << mouse.currentTile << "\n";
    } else {
        mouse.currentTile = -1;
    }
    
}

void handleMining(GLFWwindow* window,Terrain &terrain, Mouse &mouse, Player &player, GUI &gui) {

    if (mouse.currentTile == -1) return;
    
    Block block = blockData[mouse.currentTile];
    
    mouse.backpackFull = player.backpackCount >= player.equippedBackpack.capacity;
    
    bool isMineable = block.level != -1 && mouse.currentTile != 12;
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && isMineable) {
        
        
        mouse.holding += 16.6667 + player.equippedPickaxe.power*2;
        
        int blockHealth = block.hp;
        
        mouse.validPickaxeLevel =  player.equippedPickaxe.level >= block.level;
        
        if (mouse.holding > blockHealth && mouse.backpackFull == false && mouse.validPickaxeLevel) {
            terrain.mineBlock(mouse.tileX, mouse.tileY);
            std::string blockName = block.name;
            if (block.name != "special") {
                player.blockCounts[block] += 1;
                player.backpackCount += 1;
            } else {
                std::vector<Block> minedBlocks = terrain.triggerExplosion(mouse.tileX, mouse.tileY);
                for (auto &block: minedBlocks) {
                    player.blockCounts[block] += 1;
                    player.backpackCount += 1;
                }
            }
            mouse.holding = 0;
            int depth = int(abs(floor(player.coordinates.y)));

            terrain.generateBuffer(depth);
        }
        mouse.minedPercentage = (mouse.holding/blockHealth)*100;
    } else {
        mouse.holding = 0;
    }
}

void handleGUI(GLFWwindow* window,Terrain &terrain, Mouse &mouse, Player &player, const std::vector<Button> &buttons,const Vec2i &screenSize, bool mousePressed,GUI &gui, const bool atSurface) {

    if (mousePressed == false) return;
    
        float mouseY = screenSize.y-mouse.screenY;
        for (const auto &button: buttons) {
                bool validX = mouse.screenX >= button.x && mouse.screenX <= button.x+button.width;
                bool validY = mouseY >= button.y && mouseY <= button.y+button.height;
                auto it = gui.visibleButtons.find(button.id);
                bool visible = it != gui.visibleButtons.end() && it->second;
            
            
                if (validX && validY && visible) {
                    std::cout << "Pressed" << button.id << "\n";
//                    cou
                    switch(button.id) {
                        case teleport: {
                            player.platformCollision = true;
                            player.teleport(1, -2, terrain.getRawBlockIndices());
                            terrain.generateBuffer(0);
                            break;
                        }
                        case sell: {
                            if (atSurface == false) break;
                            player.backpackCount = 0;
                            for (auto &[block,count]: player.blockCounts) {
                                int totalValue = count*block.sellValue;
                                player.money += totalValue;
                                player.blockCounts[block] = 0;
                            }
                            break;
                        }
                        case oresAndShop: {
                            if (gui.openMenu == button.text) {
                                gui.openMenu = "";
                                gui.selectedTab = "pickaxes";
                                gui.setVisibleButtons({teleport,sell,oresAndShop,closeButton});
                            } else {
                                gui.openMenu = button.text;
                                if (button.text == "ores") {
                                    gui.setVisibleButtons({closeButton});
                                }
                                if (button.text == "shop") {
                                    if (atSurface) {
                                        gui.setVisibleButtons({tabSelector,pickaxeEquip,closeButton});
                                    } else {
                                        gui.openMenu = "";
                                    }
                                }
                                if (button.text == "progress") {
                                    gui.setVisibleButtons({worldSelect,closeButton});
                                }
                                
                            }
                            break;
                        }
                        case tabSelector: {
                            gui.selectedTab = button.text;
                            std::cout << "Selected tab: " << gui.selectedTab << "\n";
                            if (gui.selectedTab == "backpacks") {
                                gui.visibleButtons[pickaxeEquip] = false;
                                gui.visibleButtons[backpackEquip] = true;

                            } else if (gui.selectedTab == "pickaxes") {
                                
                                gui.visibleButtons[pickaxeEquip] = true;
                                gui.visibleButtons[backpackEquip] = false;
                            }
                            break;
                        }
                        case pickaxeEquip: {
                            if (button.text == "equipped") return;
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
                        case backpackEquip: {
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
                        case dialogueButton: {
                            if (gui.dialogue.currentLine < gui.dialogue.lineCount) {
                                gui.dialogue.currentLine +=1;
                                std::cout << "Changed to dialogue: " << gui.dialogue.currentLine << "\n";
                            } else {
                                gui.inDialogue = false;
                                gui.setVisibleButtons({teleport,oresAndShop,sell});
                                std::cout << "Finished dialgoue" << "\n";
                            }
                            break;
                        } case worldSelect: {
                            int worldIndex = std::stoi(button.metaInfo);
                            World world = worldData[worldIndex];
                            if (button.text == "equip") {
                                terrain.setupWorld(worldIndex);
                                std::cout << "Selected" << world.name << "\n";
                            } else if (player.money >= world.cost) {
                                std::cout << "Selected" << world.name << "\n";
                                player.ownedWorlds.push_back(world.name);
                                player.money -= world.cost;
                                terrain.setupWorld(worldIndex);
                            }
                            break;
                        }
                        case closeButton: {
                            gui.openMenu = "";
                            gui.setVisibleButtons({teleport,sell,oresAndShop});
                            break;
                        }
                        case dialogueChoice: {
                            std::cout << "pressed choice button" << "\n";
                            if (button.metaInfo == "SHOP") {
                                
                            } else {
                                gui.dialogue.setDialogue(std::stoi(button.metaInfo));
                            }
                        }
                    }
                    
                }
            }
        }

void handleKeyPress(GLFWwindow *window, Player &player, const Terrain &terrain, float &time) {
    
    float jumpDelay = 0.25f;
    float moveSpeed = 0.03f;
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
       player.moveSprite(-moveSpeed,0,terrain.getRawBlockIndices());
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            float currentTime = glfwGetTime();
            if (currentTime - time > jumpDelay ) {
                player.jump();
                time = currentTime;
            }
        }
   } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
       player.moveSprite(moveSpeed,0,terrain.getRawBlockIndices());
       if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
           float currentTime = glfwGetTime();
           if (currentTime - time > jumpDelay ) {
               player.jump();
               time = currentTime;
           }
       }
   } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
       float currentTime = glfwGetTime();
       if (currentTime - time > jumpDelay ) {
           player.jump();
           time = currentTime;
       }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
           player.moveSprite(-moveSpeed,0,terrain.getRawBlockIndices());
            
            
       } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
           player.moveSprite(moveSpeed,0,terrain.getRawBlockIndices());
       }
   }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        int x = floor(player.coordinates.x);
        int y = floor(-player.coordinates.y+1);
        const Tile &tile = terrain.tiles[x+y*terrainWidth];
        if (tile.textureIndex == 12) {
            player.platformCollision = false;
            std::cout << "Fallen through platform" << "\n";
        }
   }
    
    player.accelerate(terrain.getRawBlockIndices());
    
    player.collisions = {};
}
        

    
