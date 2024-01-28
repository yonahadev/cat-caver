//
//  player.cpp
//  Executable
//
//  Created by tom on 2023/11/25.
//

#include "player.hpp"
#include <iostream>
#include "vertex.hpp"
#include "quad.hpp"
#include <string>
#include "constants.hpp"

void Player::moveSprite(float x,float y, const std::vector<int> &blockIndices) {
    move(-x,0);
    update(blockIndices, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
    if (collisions.size() > 0) {
        move(x,0);
        collisions = {};
    }
    move(0,-y);
    update(blockIndices, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
    if (collisions.size() > 0) {
        if (getCollision("bottom") == true) {
            airborne = 0;
        }
        move(0,y);
    }
    update(blockIndices, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
}
Player::Player(float offsetX,float offsetY,int texIndex): Sprite(offsetX, offsetY, texIndex),equippedPickaxe(pickaxeData[0]),equippedBackpack(backpackData[0]),money(0),backpackCount(0),neighbours(){
    matrix = {1,0,-offsetX,0,1,-offsetY,0,0,1};
    
    for (const Block &block: blockData) {
        std::string blockName = block.name;
        if (block.level != -1) {
            blockCounts[block] = 0;
        }
    }
    
    ownedPickaxes[pickaxeData[0]] = true;
    ownedBackpacks[backpackData[0]] = true;
    
}

