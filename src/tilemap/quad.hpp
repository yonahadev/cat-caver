//
//  quad.hpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#ifndef quad_hpp
#define quad_hpp

#include <vector>
#include "character.hpp"

void generateQuad(int offsetX,int offsetY, int textureIndex, std::vector<float> &vertices, bool isTexture);
void generateTextQuad(const Character &currentChar, std::vector<float> &vertices);
void generateUIQuad(float width, float height, float offsetX, float offsetY, std::vector<float> &vertices, int textureIndex, bool isTexture);

#include <stdio.h>

#endif /* quad_hpp */
