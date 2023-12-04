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
    int width;
    int height;
    std::vector<int> tiles;
    VertexBuffer buffer;
    int getTile(const int x,const int y) const;
    int getTileIndex(const int x,const int y) const;
    void mineBlock(const int x,const int y);
    void generateBuffer();
    void generateLayer();
    Terrain(const std::vector<int> &tiles, const int width, const int height);
};
#endif /* terrainClass_hpp */
