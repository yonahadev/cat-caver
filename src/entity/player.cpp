//
//  player.cpp
//  Executable
//
//  Created by tom on 2023/11/25.
//

#include "player.hpp"
#include <iostream>

#include "quad.hpp"
#include <string>
#include "constants.hpp"


Player::Player(float offsetX,float offsetY,int texIndex): Sprite(offsetX, offsetY, texIndex),equippedPickaxe(pickaxeData[0]),equippedBackpack(backpackData[0]),currentQuest(questList[0]),money(0),backpackCount(0),neighbours(){

    
    for (const Block &block: blockData) {
        std::string blockName = block.name;
        if (block.sellValue != 0) {
            blockCounts[block] = 0;
        }
    }
    
    ownedWorlds.push_back(worldData[0].name);
    ownedWorlds.push_back(worldData[1].name);
    ownedWorlds.push_back(worldData[2].name);
    ownedPickaxes[pickaxeData[0]] = true;
    ownedBackpacks[backpackData[0]] = true;
    
}

