//
//  Tile.cpp
//  cat-caver
//
//  Created by tom on 2024/01/10.
//

#include "tile.hpp"

Tile::Tile(int x, int y, int textureIndex): Sprite(x, y, textureIndex), blockIndex(textureIndex) {}

void Tile::checkCollisions(const std::vector<int> &blockIndices) {
    int width = 16;
    int y = (std::floor(hitboxBottom));
    int x = std::floor(hitboxLeft);
    
    int belowBlock = blockIndices[x+(-y-1*width)];
    
                if (belowBlock != 3) {
                    collisions.push_back("bottom");

                }

}
