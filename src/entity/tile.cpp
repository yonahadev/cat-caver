//
//  Tile.cpp
//  cat-caver
//
//  Created by tom on 2024/01/10.
//

#include "tile.hpp"

Tile::Tile(int x, int y, int textureIndex): Sprite(x, y, textureIndex), blockIndex(textureIndex) {}

void Tile::checkCollisions(const std::vector<int> &blockIndices,const Hitbox &hitbox) {
    
    const int x = std::floor(coordinates.x);
    
    
    for (int y = (std::floor(hitbox.bottom)); y <= (std::floor(hitbox.top)); y++ ) {
            int currentTile = blockIndices[x+(-y*terrainWidth)];
                if (y < coordinates.y && currentTile != dirt) {
                    collisions.bottom = true;
                }
    }

}
