//
//  Tile.hpp
//  cat-caver
//
//  Created by tom on 2024/01/10.
//

#ifndef tile_hpp
#define tile_hpp

#include <stdio.h>

class Tile {
private:
public:
    int blockIndex;
    Tile(int x,int y, int textureIndex);
};

#endif /* Tile_hpp */
