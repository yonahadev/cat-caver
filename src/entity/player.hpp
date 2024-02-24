//
//  player.hpp
//  Executable
//
//  Created by tom on 2023/11/25.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "sprite.hpp"
#include "mat3.hpp"
#include "vertexBuffer.hpp"
#include "vertexArray.hpp"
#include "vec2.hpp"
#include "terrain.hpp"
#include <vector>
#include <string>
#include <map>
#include "Block.hpp"
#include "pickaxe.hpp"
#include "backpack.hpp"

class Player: public Sprite {
public:
    Pickaxe equippedPickaxe;
    Backpack equippedBackpack;
    std::map<Block, int> blockCounts;
    std::unordered_map<Pickaxe, bool> ownedPickaxes;
    std::unordered_map<Backpack, bool> ownedBackpacks;
    std::vector<std::string> ownedWorlds;
    Quest currentQuest;
    int money;
    int backpackCount;
    std::vector<Vec2i> neighbours;
    Player(float offsetX,float offsetY,int texIndex);
};

#endif /* player_hpp */
