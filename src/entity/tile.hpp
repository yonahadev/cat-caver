//
//  Tile.hpp
//  cat-caver
//
//  Created by tom on 2024/01/10.
//

#ifndef tile_hpp
#define tile_hpp

#include <stdio.h>
#include "sprite.hpp"

class Tile: public Sprite {
private:
public:
    int blockIndex;
    Vec2i lastUpdatedCoordinates = {0,0};
    Tile(int x,int y, int textureIndex, float airborne);
    Tile(int x,int y, int textureIndex);
    void checkCollisions(const std::vector<int> &blockIndices, const Hitbox &hitbox) override;
};

#endif /* Tile_hpp */
