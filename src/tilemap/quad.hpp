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

void generateQuad(const int offsetX,const int offsetY, const int textureIndex, std::vector<Vertex> &vertices);
void generateTextQuad(const int offsetX,const int offsetY,const Character &currentChar, std::vector<Vertex> &vertices);
void generateUIQuad(const float width, const float height, const float offsetX, const float offsetY, std::vector<Vertex> &vertices);

#include <stdio.h>

#endif /* quad_hpp */
