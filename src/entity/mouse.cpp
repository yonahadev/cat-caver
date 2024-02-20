//
//  cpp
//  cat-caver
//
//  Created by tom on 2023/12/16.
//
#include "mouse.hpp"
#include "quad.hpp"
#include "constants.hpp"

void Mouse::generateBuffer() {
    if (holding > 0 && backpackFull == false && validPickaxeLevel) {
        float mined = minedPercentage/100.0f;

        float reverse = (1-mined)/2;
        float startX = tileX+reverse;
        float startY = tileY+reverse;

        std::vector<float> vertices;
        generateUIQuad(mined,mined,startX,startY,vertices,1,false);
        
        vao.bindArray();
        vbo.bindBuffer();
        vbo.bindData(vertices,2);
        vao.enableAttributes(2);
        vao.unbindArray();
    } else {
        bool isMineable = blockData[currentTile].level != -1 && blockData[currentTile].level != 99;
        if (currentTile != -1 && isMineable ) {
            std::vector<float> vertices;
            generateQuad(tileX,tileY,4,vertices,false);
            vao.bindArray();
            vbo.bindBuffer();
            vbo.bindData(vertices,2);
            vao.enableAttributes(2);
            vao.unbindArray();
        } else {
            vbo.verticesCount = 0;
        }
    }
}
