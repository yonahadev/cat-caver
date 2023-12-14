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

std::vector<int> Terrain::simulateTurn(const std::vector<int> &currentTiles, const int layerDepth) {
    std::vector<int> newTiles = {};
    for (int y = 0; y < layerDepth; y++) {
        for (int x = 0; x < config.width; x++) {
            int currentCell = currentTiles[x+(y*config.width)];
            std::cout << "Current cell is:  " << currentCell << "\n";
            std::vector<Vec2i> currentNeighbours = getNeighbours(x, y);
            int newCell = calculateCellState(currentNeighbours, currentCell);
            newTiles.push_back(newCell);
        }
    }
    return newTiles;
}

unsigned int Terrain::getAliveNeighbourCount(const std::vector <Vec2i> &neighbours) const {
    unsigned int aliveCount = 0;
    
    for (auto &neighbour: neighbours) {
        if (getTile(neighbour.x,neighbour.y) == 1) {
            aliveCount++;
        }
    }
    
    return aliveCount;
}

int Terrain::calculateCellState(const std::vector <Vec2i> &neighbours,const unsigned int cell) const {
    
    int aliveCount = getAliveNeighbourCount(neighbours);
    
    std::cout << "Current cell Alive count:  " << aliveCount << "\n";
    
    if (cell == 1) {
        if (aliveCount <= config.underpopulationCount || aliveCount >= config.overpopulationCount) {
            return 0;
        } else {
            return 1;
        }
    }
    
    if (aliveCount >= config.cellsForBirth) {
        return 1;
    }
    
    return 0;
}

std::vector<Vec2i> Terrain::getNeighbours(const int x, const int y) const {
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


int Terrain::getTile(const int x,const int y) const{
    int index = getTileIndex(x,y);
    return tiles[index];
}

//int Terrain::getBlockHP(const int tile) const {
//    int hp = block
//    return hp;
//}
//
//std::string Terrain::getBlockName(const int tile) const {
//    return blockData["blocks"][tile]["name"];
//}
//
//bool Terrain::isCollideable(const int tile) const {
//    bool collideable = blockData["blocks"][tile]["canMine"];
//    if (collideable) {
//        return true;
//    }
//    return false;
//}

int Terrain::getTileIndex(const int x, const int y) const{
    return x+(-y*config.width);
}

void Terrain::mineBlock(const int x, const int y) {
    int index = getTileIndex(x,y);
    tiles[index] = 3;
}

void Terrain::generateLayer() {
    int layerDepth = 50;
    std::vector<int> layerTiles {};
    for (int i = 0; i < layerDepth; i++) {
        for (int j = 0; j < config.width; j++) {
            if (j == 0 || j == config.width-1) {
                layerTiles.push_back(1);
            } else {
                int cell = 0;
                if (getRandomInt(1, 100) <= config.startingAliveChance) {
                    cell = 1;
                }
                layerTiles.push_back(cell);

            }
        }
    }
    
    for (int i = 0; i < config.turnCount; i++) {
        layerTiles = simulateTurn(layerTiles,layerDepth);
    }
    
    tiles.insert(tiles.end(), layerTiles.begin(),layerTiles.end());
    
    height += layerDepth;
    
    generateBuffer();
}

void Terrain::generateBuffer() {
    std::vector<Vertex> vertices;
    for (int y = 0; y<height; y++) {
        for (int x = 0; x<config.width; x++) {
            generateQuad(x, -y, tiles[x+y*config.width], vertices);
        }
    }
    vbo = VBO();
    vao = VAO();
    vao.bindArray();
    vbo.bindBuffer();
    vbo.bindData(vertices);
    vao.enableAttributes();
    vao.unbindArray();
}

Terrain::Terrain(const DungeonConfig &config, const std::vector<Block> &blockData): config(config),blockData(blockData) {
    int startingHeight = 5;
    for (int i = 0; i < startingHeight; i++) {
        for (int j = 0; j < config.width; j++) {
            if (j == 0 || j == config.width-1 || i == 0) {
                tiles.push_back(1);
            } else {
                tiles.push_back(3);
            }
        }
    }
    height = startingHeight;
    generateBuffer();
}
