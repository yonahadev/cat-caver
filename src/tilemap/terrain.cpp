//
//  terrainClass.cpp
//  Executable
//
//  Created by tom on 2023/10/11.
//

#include "terrain.hpp"
#include "quad.hpp"
#include <iostream>
#include <fstream>

int Terrain::getTile(const int x,const int y) const{
    int index = getTileIndex(x,y);
    return tiles[index];
}

int Terrain::getBlockHP(const int tile) const {
    int hp = blockData["blocks"][tile]["time"];
    return hp;
}

bool Terrain::isCollideable(const int tile) const {
    bool collideable = blockData["blocks"][tile]["canMine"];
    if (collideable) {
        return true;
    }
    return false;
}

int Terrain::getTileIndex(const int x, const int y) const{
    return x+(-y*width);
}

void Terrain::mineBlock(const int x, const int y) {
    int index = getTileIndex(x,y);
    tiles[index] = 3;
}

void Terrain::generateLayer() {
    int layerDepth = 5;
    
    for (int y = 0; y<layerDepth; y++) {
        for (int x = 0; x<width; x++) {
            if (x == 0 || x == width-1) {
                tiles.push_back(1);
            } else {
                tiles.push_back(4);
            }
        }
    }
    
    height += layerDepth;
    
    generateBuffer();
    
//    std::cout << "Generated layer at" << height << "\n";
}

void Terrain::generateBuffer() {
    std::vector<Vertex> vertices;
    for (int y = 0; y<height; y++) {
        for (int x = 0; x<width; x++) {
            generateQuad(x, -y, tiles[x+y*width], vertices);
        }
    }
    buffer = VertexBuffer(vertices);
}

Terrain::Terrain(const std::vector<int> &tiles, const int width, const int height): tiles(tiles), width(width),height(height) {
    std::ifstream file("/Users/tom/Documents/cplusplus/cat-caver/res/blockData.json");
    blockData = json::parse(file);
    generateBuffer();
};
