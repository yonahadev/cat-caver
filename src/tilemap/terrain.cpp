//
//  terrainClass.cpp
//  Executable
//
//  Created by tom on 2023/10/11.
//

#include "terrain.hpp"
#include "quad.hpp"
#include <iostream>

Terrain::Terrain(const std::vector<int> &tiles, const int width, const int height) {
    std::vector<Vertex> vertices;
    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
//            std::cout << x << "," << y << "\n";
            generateQuad(x, -y, tiles[x+y*width], vertices);
        }
    }
    buffer = VertexBuffer(vertices);
};
