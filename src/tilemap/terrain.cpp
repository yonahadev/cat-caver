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
#include "math.hpp"
#include "PerlinNoise.hpp"
#include "tile.hpp"
#include "glad/glad.h"

std::vector<Vec2i> Terrain::getNeighbours(int x,int y) const {
    std::vector <Vec2i> neighbours = {};
    if (x > 1) {
        Vec2i left = {x-1,y};
        neighbours.push_back(left);
        if (y != height-1) {
            Vec2i topLeft = {x-1, y-1};
            neighbours.push_back(topLeft);
        }
        if (y != 0) {
            Vec2i bottomLeft = {x-1, y+1};
            neighbours.push_back(bottomLeft);
        }
    }
    if (x < config.width-2) {
        Vec2i right = {x+1,y};
        neighbours.push_back(right);
        if (y != height-1) {
            Vec2i topRight = {x+1, y-1};
            neighbours.push_back(topRight);
        }
        if (y != 0) {
            Vec2i bottomRight = {x+1, y+1};
            neighbours.push_back(bottomRight);
        }
    }
    if (y != 0) {
        Vec2i top = {x,y-1};
        neighbours.push_back(top);
    }
    if (y != height-1) {
        Vec2i bottom = {x,y+1};
        neighbours.push_back(bottom);
    }
    
    return neighbours;
}

std::vector<int> Terrain::getRawBlockIndices() const {
    std::vector<int> blockIndices;
    for (const Tile &tile: tiles) {
        blockIndices.push_back(tile.blockIndex);
    }
    return blockIndices;
}

int Terrain::getTile(int x,int y) const{
    int index = getTileIndex(x,y);
    return tiles[index].blockIndex;
}

int Terrain::getTileIndex(int x,int y) const{
    return x+(-y*config.width);
}

void Terrain::mineBlock(int x, int y) {
    int index = getTileIndex(x,y);
    tiles[index] = Tile(x,y,3);
}

std::vector<Block> Terrain::triggerExplosion(const int x, const int y) {
//    std::cout << "explosion event" << "\n";
    std::vector<Block> minedBlocks {};
    const int radius = 2;
    for (int i = -radius; i <= radius; i++) {
        const int currentX = x+i;
        for (int j = -radius; j <= radius; j++) {
            const int currentY = y+j;
            const Block block = blockData[getTile(currentX, currentY)];
            const double squaredX = (x-currentX)*(x-currentX);
            const double squaredY = (y-currentY)*(y-currentY);
            const double dist = sqrt(squaredX+squaredY);
            if (block.level != -1 && block.name != "special" && dist <= static_cast<double>(radius)) {
                mineBlock(x+i, y+j);
                minedBlocks.push_back(block);
            }
        }
    }
    return minedBlocks;
}



int Terrain::getRandomOre(const std::map<int,double> &layerOres,const int x, const int y, const int layerDepth, const int layerWidth) { //only works for sets with a total of 100
    
    const siv::PerlinNoise::seed_type seed = 567090;
    const siv::PerlinNoise perlin{seed};
    const double noiseFactor = 0.2;
    const double xPos = double(x)*noiseFactor;
    const double yPos = double(y)*noiseFactor;
    const double noise = perlin.normalizedOctave2D_01(xPos, yPos,3);
    
    const double distanceFromCenter = abs(0.5-noise);
    
//    std::cout << "X position: " << xPos << " Y position: " << yPos << "\n";
//    std::cout << "Noise value: " << std::to_string(noise) << " distance from center: "  << std::to_string(distanceFromCenter) << "\n";
        
    for (auto &[ore,magnitude]:layerOres) {
//        std::cout << "total: " << magnitude << "\n";
        if (distanceFromCenter <= magnitude) {
            return ore;
        }
    }
    std::cout << "FAILED TO SELECT AN ORE" << "\n";
    return 0;
}

void Terrain::generateLayer() {
    
    for (int y = 0; y < 40; y++) {
        for (int x = 0; x < 16; x++ ) {
            tiles.emplace_back(x,-height-y,0);
        }
    }
    
    height += config.layerDepth;
    
    layerCount += 1;

    generateBuffer();
}

void Terrain::generateBuffer() {
    instanceCount = 0;
    int textureCount = 10;
    
    std::vector<float> texels; //only need x texels
    std::vector<Mat3> matrices; //tile matrices so we can pass to the instance draw call
    
    for (Tile &tile: tiles) {
        instanceCount += 1;
        
        matrices.push_back(tile.matrix);
        
        int textureIndex = tile.textureIndex;
        float textureStart = float(textureIndex)/textureCount;
        float textureEnd = (textureIndex+1.0f)/textureCount;
        
        texels.push_back(textureStart); //0,0 tex coords
        
        texels.push_back(textureEnd); //1,0 tex coords
        
        std::cout << "Texels: " << textureStart << "," << textureEnd << "\n";
    }
    
    std::vector<float> modelMatrices;
    
    for (Mat3 &mat: matrices) {
        mat.transpose(modelMatrices);
    }
    
    vao.bindArray();
    matrixVBO.bindBuffer();
    
    glBufferData(GL_ARRAY_BUFFER,modelMatrices.size()*sizeof(float),modelMatrices.data(),GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 9 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    
    
    texelsVBO.bindBuffer();
    
    glBufferData(GL_ARRAY_BUFFER,texels.size()*sizeof(float),texels.data(),GL_DYNAMIC_DRAW);
    glVertexAttribPointer(4,2,GL_FLOAT,GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);
    
}

Terrain::Terrain(const DungeonConfig &config, const std::vector<Block> &blockData): config(config),layerCount(0),tiles(),blockData(blockData) {
    
    std::vector<float> instanceVertices = {
        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,0.0f,
        1.0f,1.0f,
        0.0f,1.0f
    };
    
    vao.genArrays();
    vertexVBO.genBuffer();
    matrixVBO.genBuffer();
    texelsVBO.genBuffer();
    
    vao.bindArray();
    vertexVBO.bindBuffer();
    
    glBufferData(GL_ARRAY_BUFFER,instanceVertices.size()*sizeof(float),instanceVertices.data(),GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    
    int startingHeight = 5;
    for (int i = 0; i < startingHeight; i++) {
        for (int j = 0; j < config.width; j++) {
            if ( j == config.width-1 || i == 0 || j == 0) {
                tiles.emplace_back(j,-i,7);
            } else {
                tiles.emplace_back(j,-i,3);
            }
        }
    }
    height = startingHeight;
    
    generateBuffer();
}
