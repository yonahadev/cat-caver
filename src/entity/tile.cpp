//
//  Tile.cpp
//  cat-caver
//
//  Created by tom on 2024/01/10.
//

#include "tile.hpp"

Tile::Tile(int x, int y, int textureIndex): Sprite(x, y, textureIndex), blockIndex(textureIndex) {}

void Tile::checkCollisions(const std::vector<int> &blockIndices) {
    
    const int x = std::floor(coordinates.x);
    
    
    for (int y = (std::floor(hitboxBottom)); y <= (std::floor(hitboxTop)); y++ ) {
            int currentTile = blockIndices[x+(-y*terrainWidth)];
                if (y < coordinates.y && currentTile != 3 ) {
                    collisions.push_back("bottom");
                }
    }

}
