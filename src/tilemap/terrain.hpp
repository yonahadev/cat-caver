//
//  terrainClass.hpp
//  Executable
//
//  Created by tom on 2023/10/11.
//
#ifndef terrain_hpp
#define terrain_hpp

#include <stdio.h>
#include <vector>
#include "vertex.hpp"
#include "vertexBuffer.hpp"

class Terrain {
private:
public:
    VertexBuffer buffer;
    Terrain(const std::vector<int> &tiles, const int width, const int height);
};
#endif /* terrainClass_hpp */
