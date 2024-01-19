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
#include <unordered_map>
#include "Block.hpp"
#include "pickaxe.hpp"
#include "backpack.hpp"

class Player: public Sprite {
public:
    Pickaxe equippedPickaxe;
    Backpack equippedBackpack;
    std::unordered_map<Block, int> blockCounts;
    std::unordered_map<Pickaxe, bool> ownedPickaxes;
    std::unordered_map<Backpack, bool> ownedBackpacks;
    int money;
    int backpackCount;
    std::vector<Vec2i> neighbours;
    void moveSprite(const float x,const float y, const std::vector<int> &blockIndices);
    Player(float offsetX,float offsetY, const int textureIndex, const std::unordered_map<Block, int> &map);
};

#endif /* player_hpp */
