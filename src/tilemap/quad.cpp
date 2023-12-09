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
    float endX = (ch.x+ch.width)/199.0f;
    float startX = ch.x/199.0f;
    float endY = 1-(ch.y/199.0f);
    float startY = 1-((ch.y+ch.height)/199.0f);
//    std::cout << "endx: " <<  endX  << " startX: "<< startX << " endY: " << endY << " startY: "  << startY << "\n";
    
    float posX = 0.0f + offsetX;
    float endPosX = posX + ch.width;
    float posY = 0.0f + offsetY;
    float endPosY = posY + ch.height;
    
        vertices.emplace_back(posX,posY,          startX,startY);
        vertices.emplace_back(endPosX,posY,         endX,startY);
        vertices.emplace_back(endPosX,endPosY,        endX,endY);
        vertices.emplace_back(posX,posY,          startX,startY);
        vertices.emplace_back(endPosX,endPosY,        endX,endY);
        vertices.emplace_back(posX,endPosY,         startX,endY);
}

void generateUIQuad(const float width, const float height, const float offsetX, const float offsetY, std::vector<Vertex> &vertices) {
    
    int textureIndex = 1;
    float textureEnd = (textureIndex+1) * 0.125f;
    float textureStart = textureIndex * 0.125f;
    
    float posX = 0.0f + offsetX;
    float endPosX = posX + width;
    float posY = 0.0f + offsetY;
    float endPosY = posY + height;
    
        vertices.emplace_back(posX,posY,          textureStart,0.0f);
        vertices.emplace_back(endPosX,posY,         textureEnd,0.0f);
        vertices.emplace_back(endPosX,endPosY,        textureEnd,1.0f);
        vertices.emplace_back(posX,posY,          textureStart,0.0f);
        vertices.emplace_back(endPosX,endPosY,        textureEnd,1.0f);
        vertices.emplace_back(posX,endPosY,         textureStart,1.0f);
}
