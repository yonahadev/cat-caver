//
//  quad.cpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#include "quad.hpp"
#include <iostream>

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

void generateTextQuad(const int offsetX,const int offsetY,const Character &ch, std::vector<Vertex> &vertices) {
    float endX = (ch.x+ch.width)/278.0f;
    float startX = ch.x/278.0f;
    float endY = 1-(ch.y/278.0f);
    float startY = 1-((ch.y+ch.height)/278.0f);
    std::cout << "endx: " <<  endX  << " startX: "<< startX << " endY: " << endY << " startY: "  << startY << "\n";
    
        vertices.emplace_back(0.0f,0.0f,          startX,startY);
        vertices.emplace_back(1.0f,0.0f,         endX,startY);
        vertices.emplace_back(1.0f,1.0f,        endX,endY);
        vertices.emplace_back(0.0f,0.0f,          startX,startY);
        vertices.emplace_back(1.0f,1.0f,        endX,endY);
        vertices.emplace_back(0.0f,1.0f,         startX,endY);
}

