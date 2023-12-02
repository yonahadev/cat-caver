//
//  terrainClass.cpp
//  Executable
//
//  Created by tom on 2023/10/11.
//

#include "terrain.hpp"
#include "quad.hpp"
#include <iostream>

Terrain::Terrain() {};

void Terrain::generateLayer(const int offsetX, const int offsetY) {
    std::vector<Vertex> layerVertices;
    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
            generateQuad(offsetX+x, -(offsetY+y), tiles[x+y*width], layerVertices);
        }
    }
    layers.emplace_back(layerVertices,tiles);
};

