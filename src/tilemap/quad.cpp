//
//  quad.cpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#include "quad.hpp"

void generateQuad(int offsetX, int offsetY, const int textureIndex, std::vector<Vertex> &vertices) {
    float textureEnd = textureIndex*0.125;
    float textureStart = (textureIndex-1)*0.125;
    if (textureIndex > 0) {
        vertices.emplace_back(0.0f+offsetX,0.0f+offsetY,          textureStart,0.0f);
        vertices.emplace_back(1.0f+offsetX,0.0f+offsetY,         textureEnd,0.0f);
        vertices.emplace_back(1.0f+offsetX,1.0f+offsetY,        textureEnd,1.0f);
        vertices.emplace_back(0.0f+offsetX,0.0f+offsetY,          textureStart,0.0f);
        vertices.emplace_back(1.0f+offsetX,1.0f+offsetY,        textureEnd,1.0f);
        vertices.emplace_back(0.0f+offsetX,1.0f+offsetY,         textureStart,1.0f);
    }
}
