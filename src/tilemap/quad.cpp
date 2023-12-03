//
//  quad.cpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#include "quad.hpp"

void generateQuad(const int offsetX,const int offsetY, const int textureIndex, std::vector<Vertex> &vertices) {
    float textureEnd = (textureIndex+1) * 0.125f;
    float textureStart = textureIndex * 0.125f;
        vertices.emplace_back(0.0f+offsetX,0.0f+offsetY,          textureStart,0.0f);
        vertices.emplace_back(1.0f+offsetX,0.0f+offsetY,         textureEnd,0.0f);
        vertices.emplace_back(1.0f+offsetX,1.0f+offsetY,        textureEnd,1.0f);
        vertices.emplace_back(0.0f+offsetX,0.0f+offsetY,          textureStart,0.0f);
        vertices.emplace_back(1.0f+offsetX,1.0f+offsetY,        textureEnd,1.0f);
        vertices.emplace_back(0.0f+offsetX,1.0f+offsetY,         textureStart,1.0f);
}
