//
//  terrainClass.cpp
//  Executable
//
//  Created by tom on 2023/10/11.
//

#include "terrain.hpp"
#include "quad.hpp"
#include <iostream>


int Terrain::getTile(const int x,const int y) const{
    return tiles[x+(-y*width)];
}

Terrain::Terrain(const std::vector<int> &tiles, const int width, const int height): tiles(tiles), width(width),height(height) {
    std::vector<Vertex> vertices;
    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
            generateQuad(x, -y, tiles[x+y*width], vertices);
        }
    }
    buffer = VertexBuffer(vertices);
};
