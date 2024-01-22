//
//  cpp
//  cat-caver
//
//  Created by tom on 2023/12/16.
//
#include "mouse.hpp"
#include "quad.hpp"

void Mouse::generateBuffer(const std::vector<Block> &blockData) {
    if (holding > 0 && backpackFull == false) {
        float mined = minedPercentage/100.0f;

        float reverse = (1-mined)/2;
        float startX = tileX+reverse;
        float startY = tileY+reverse;

        std::vector<Vertex> vertices;
        generateUIQuad(mined,mined,startX,startY,vertices);
        
        vao.bindArray();
        vbo.bindBuffer();
        vbo.bindData(vertices);
        vao.enableAttributes();
        vao.unbindArray();
    } else {
        bool isMineable = blockData[currentTile].level != -1;
        if (currentTile != -1 && isMineable ) {
    //        std::cout << currentTile << "\n";
            std::vector<Vertex> vertices;
            generateQuad(tileX,tileY,4,vertices);
            vao.bindArray();
            vbo.bindBuffer();
            vbo.bindData(vertices);
            vao.enableAttributes();
            vao.unbindArray();
        } else {
    //        std::cout << "invalid mouse position" << "\n";
            vbo.verticesCount = 0;
        }
    }
}
