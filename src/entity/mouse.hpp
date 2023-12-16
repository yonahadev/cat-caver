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
#include "vertexArray.hpp"
#include "block.hpp"

class Mouse {
private:
public:
    VBO vbo;
    VAO vao;
    int minedPercentage;
    int currentTile;
    int tileX;
    int tileY;
    float holding;
    void generateBuffer(const std::vector<Block> &blockData);
};

#endif /* mouse_hpp */
