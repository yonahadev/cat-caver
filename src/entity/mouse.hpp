//
//  mouse.hpp
//  cat-caver
//
//  Created by tom on 2023/12/04.
//

#ifndef mouse_hpp
#define mouse_hpp

#include <stdio.h>
#include "vertexBuffer.hpp"

class Mouse {
private:
public:
    VertexBuffer buffer;
    int currentTile;
    int tileX;
    int tileY;
    float holding;
};

#endif /* mouse_hpp */
