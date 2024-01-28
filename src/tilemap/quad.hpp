//
//  quad.hpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#ifndef quad_hpp
#define quad_hpp

#include "vertex.hpp"
#include <vector>
#include "character.hpp"

void generateQuad(int offsetX,int offsetY, int textureIndex, std::vector<Vertex> &vertices);
void generateTextQuad(const Character &currentChar, std::vector<Vertex> &vertices);
void generateUIQuad(float width, float height, float offsetX, float offsetY, std::vector<Vertex> &vertices, int textureIndex);

#include <stdio.h>

#endif /* quad_hpp */
