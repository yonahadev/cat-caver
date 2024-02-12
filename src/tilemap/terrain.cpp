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
#include "constants.hpp"


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
    if (x < terrainWidth-2) {
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
    return x+(-y*terrainWidth);
}

void Terrain::mineBlock(int x, int y) {
    int index = getTileIndex(x,y);
    tiles[index] = Tile(x,y,dirt);
}

std::vector<Block> Terrain::triggerExplosion(int x, int y) {
    std::vector<Block> minedBlocks {};
    int radius = 2;
    for (int i = -radius; i <= radius; i++) {
        int currentX = x+i;
        for (int j = -radius; j <= radius; j++) {
            int currentY = y+j;
            const Block block = blockData[getTile(currentX, currentY)];
            const double squaredX = (x-currentX)*(x-currentX);
            const double squaredY = (y-currentY)*(y-currentY);
            const double dist = sqrt(squaredX+squaredY);
            if (block.level != -1 && block.name != "tnt" && dist <= static_cast<double>(radius)) {
                mineBlock(x+i, y+j);
                minedBlocks.push_back(block);
            }
        }
    }
    return minedBlocks;
}



int Terrain::getRandomOre(int layer,int x,int y) const { //only works for sets with a total of 100
    
    const siv::PerlinNoise::seed_type seed = 567090;
    const siv::PerlinNoise perlin{seed};
    const double noiseFactor = 0.2;
    const double xPos = double(x)*noiseFactor;
    const double yPos = double(y)*noiseFactor;
    const double noise = perlin.normalizedOctave2D_01(xPos,yPos,3);
    
    const double distanceFromCenter = abs(0.5-noise);
    
//    std::cout << "X position: " << xPos << " Y position: " << yPos << "\n";
//    std::cout << "Noise value: " << std::to_string(noise) << " deviation: "  << std::to_string(distanceFromCenter) << "\n";
        
    for (auto &[magnitude,ore]:worldData[currentWorld].layerInfo[layer]) {
//        std::cout << "Ore: " << ore << " Magnitude: " << magnitude << "\n";
        if (distanceFromCenter <= magnitude) {
//            std::cout << "Deviation: " << distanceFromCenter  << " tile: " << ore << "\n";
            return ore;
        }
    }
    std::cout << "VALUE OUT OF RANGE" << "\n";
    return 0;
}

void Terrain::generateLayer(int depth) {
    
//    std::cout << "Current world: " << worldData[currentWorld].name << "\n";

    
    for (int y = 0; y < layerDepth; y++) {
        for (int x = 0; x < terrainWidth; x++ ) {
            bool borderTile = x == 0 || x == terrainWidth -1;
            if (borderTile) {
                tiles.emplace_back(x,-height-y,bedrock);
            } else {
                oreLayer = layerCount;
                int lastLayer = static_cast<int>(worldData[currentWorld].layerInfo.size())-1;
                if (layerCount > lastLayer) {
                    oreLayer = lastLayer;
                }
//                std::cout << "Current layer: " << layer << "\n";
                int blockIndex = getRandomOre(oreLayer,x,y);
                tiles.emplace_back(x,-height-y,blockIndex);
            }
        }
    }
    
    height += layerDepth;
    
    layerCount += 1;

    generateBuffer(depth);
}

void Terrain::generateBuffer(int depth) {
    instanceCount = 0;
    
    generatedDepth = depth;
    
    std::vector<float> texels; //only need x texels
    std::vector<Mat3> matrices; //tile matrices so we can pass to the instance draw call
    
    int renderTop;
    
    if (depth <= 6) {
        renderTop = 0;
    } else {
        renderTop = depth-6;
    }
    
    
    
    for (int y = renderTop; y < renderTop+20; y++) {
        for (int x = 0; x < terrainWidth; x++) {
            
            Tile &tile = tiles[x+y*terrainWidth];
            
            instanceCount += 1;
            int textureIndex = tile.textureIndex;
            
            float textureStart = textureIndex * textureMultiplier;
            float textureEnd = (textureIndex+1) * textureMultiplier;
            
            
            if (tile.blockIndex != dirt) {
                matrices.push_back(tile.matrix);
                texels.push_back(textureStart); //0,0 tex coords
                texels.push_back(textureEnd); //1,0 tex coords
            }
        }
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
    
    backgroundVAO.bindArray();
    backgroundVBO.bindBuffer();
    
    std::vector<Vertex> vertices;
    
    for (int y = -10; y < height; y++) {
        for (int x = -10; x < terrainWidth+10; x++) {
            int textureIndex;
            if (x < 0 || x > terrainWidth-1 || y < 0) {
                textureIndex = bedrock;
            } else {
                textureIndex = dirt;
            }
            generateQuad(x, -y, textureIndex, vertices);
        }
    }
    
    backgroundVBO.bindData(vertices);
    backgroundVAO.enableAttributes();
    
}

void Terrain::setupWorld(int worldIndex) {
    currentWorld = worldIndex;
    layerCount = 0;
    int startingHeight = 10;
    tiles = std::vector<Tile>{};
    for (int i = 0; i < startingHeight; i++) {
        for (int j = 0; j < terrainWidth; j++) {
            if ( j == terrainWidth-1 || i == 0 || j == 0) {
                tiles.emplace_back(j,-i,bedrock);
            } else if (i == 5) {
                tiles.emplace_back(j,-i,bedrock);
            }
            else {
                tiles.emplace_back(j,-i,dirt);
            }
        }
    }
    height = startingHeight;
    
    generateBuffer(0);
};

Terrain::Terrain(): layerCount(0),tiles(),currentWorld(0) {
    
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
    backgroundVAO.genArrays();
    backgroundVBO.genBuffer();
    
    vao.bindArray();
    vertexVBO.bindBuffer();
    
    glBufferData(GL_ARRAY_BUFFER,instanceVertices.size()*sizeof(float),instanceVertices.data(),GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    
    setupWorld(0);

}
