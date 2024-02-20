//
//  quad.cpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#include "quad.hpp"
#include <iostream>
#include "constants.hpp"

void generateQuad(int offsetX,int offsetY, int textureIndex, std::vector<float> &vertices, bool isTexture) {

    
    float texture = static_cast<float>(textureIndex);

    std::vector<float> bottomLeft;
    std::vector<float> bottomRight;
    std::vector<float> topRight;
    std::vector<float> topLeft;

    if (isTexture) {
        bottomLeft = {0.0f+offsetX,0.0f+offsetY,          0.0f,0.0f,texture};
        bottomRight = {1.0f+offsetX,0.0f+offsetY,         1.0f,0.0f,texture};
        topRight = {1.0f+offsetX,1.0f+offsetY,        1.0f,1.0f,texture};
        topLeft = {0.0f+offsetX,1.0f+offsetY,         0.0f,1.0f,texture};
    } else {
        bottomLeft = {0.0f+offsetX,0.0f+offsetY};
        bottomRight = {1.0f+offsetX,0.0f+offsetY};
        topRight = {1.0f+offsetX,1.0f+offsetY};
        topLeft = {0.0f+offsetX,1.0f+offsetY};
    }
    
    
    vertices.insert(vertices.end(), bottomLeft.begin(),bottomLeft.end());
    vertices.insert(vertices.end(), bottomRight.begin(),bottomRight.end());
    vertices.insert(vertices.end(), topRight.begin(),topRight.end());
    
    vertices.insert(vertices.end(), bottomLeft.begin(),bottomLeft.end());
    vertices.insert(vertices.end(), topRight.begin(),topRight.end());
    vertices.insert(vertices.end(), topLeft.begin(),topLeft.end());
}

void generateTextQuad(const Character &ch, std::vector<float> &vertices) {
    float endX = (ch.x+ch.width)/199.0f;
    float startX = ch.x/199.0f;
    float endY = 1-(ch.y/199.0f);
    float startY = 1-((ch.y+ch.height)/199.0f);
    
    float posX = 0.0f + ch.xOffset;
    float endPosX = posX + ch.width;
    float posY = 0.0f + ch.yOffset;
    float endPosY = posY + ch.height;
    
    std::vector<float> bottomLeft {posX,posY,          startX,startY};
    std::vector<float> bottomRight {endPosX,posY,        endX,startY};
    std::vector<float> topRight {endPosX,endPosY,       endX,endY};
    std::vector<float> topLeft {posX,endPosY,           startX,endY};

    vertices.insert(vertices.end(), bottomLeft.begin(),bottomLeft.end());
    vertices.insert(vertices.end(), bottomRight.begin(),bottomRight.end());
    vertices.insert(vertices.end(), topRight.begin(),topRight.end());
    
    vertices.insert(vertices.end(), bottomLeft.begin(),bottomLeft.end());
    vertices.insert(vertices.end(), topRight.begin(),topRight.end());
    vertices.insert(vertices.end(), topLeft.begin(),topLeft.end());
}

void generateUIQuad(float width, float height, float offsetX, float offsetY, std::vector<float> &vertices, int textureIndex, bool isTexture) {
    
    float posX = 0.0f + offsetX;
    float endPosX = posX + width;
    float posY = 0.0f + offsetY;
    float endPosY = posY + height;
    
    float texture = static_cast<float>(textureIndex);
    
    std::vector<float> bottomLeft;
    std::vector<float> bottomRight;
    std::vector<float> topRight;
    std::vector<float> topLeft;
    
    if (isTexture) {
        bottomLeft = {posX,posY,          0.0f,0.0f,texture};
        bottomRight = {endPosX,posY,        1.0f,0.0f,texture};
        topRight = {endPosX,endPosY,       1.0f,1.0f,texture};
        topLeft = {posX,endPosY,           0.0f,1.0f,texture};
    } else {
        std::cout << "Generating non textured ui quad" << "\n";
        bottomLeft = {posX,posY};
        bottomRight = {endPosX,posY};
        topRight = {endPosX,endPosY};
        topLeft = {posX,endPosY};

    }
    
    vertices.insert(vertices.end(), bottomLeft.begin(),bottomLeft.end());
    vertices.insert(vertices.end(), bottomRight.begin(),bottomRight.end());
    vertices.insert(vertices.end(), topRight.begin(),topRight.end());
     
    vertices.insert(vertices.end(), bottomLeft.begin(),bottomLeft.end());
    vertices.insert(vertices.end(), topRight.begin(),topRight.end());
    vertices.insert(vertices.end(), topLeft.begin(),topLeft.end());
}
