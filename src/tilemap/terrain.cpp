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

std::vector<int> Terrain::simulateTurn(const std::vector<int> &currentTiles, const int layerDepth, const std::unordered_map<int,double> &layerOres) {
    std::vector<int> newTiles = {};
    for (int y = 0; y < layerDepth; y++) {
        for (int x = 1; x < config.width-1; x++) {
            int currentCell = currentTiles[y*config.width + x];
            std::cout << "Current cell is:  " << currentCell << "\n";
            std::vector<Vec2i> currentNeighbours = getNeighbours(x, y);
            int newCell = calculateCellState(currentNeighbours, currentCell, currentTiles,layerOres);
            newTiles.push_back(newCell);
        }
    }
    return newTiles;
}

std::unordered_map<int, int> Terrain::getNeighbourOres(const std::vector <Vec2i> &neighbours,const std::vector<int> &currentTiles, const std::unordered_map<int,double> &layerOres) const {
    
    std::unordered_map<int, int> neighbouringOres;
    
    for (auto &neighbour: neighbours) {
        int currentTile = currentTiles[neighbour.y*config.width+neighbour.x];
        neighbouringOres[currentTile] += 1;
    }
    
    return neighbouringOres;
}

int Terrain::calculateCellState(const std::vector<Vec2i> &neighbours, const unsigned int cell, const std::vector<int> &currentTiles, const std::unordered_map<int,double> &layerOres) const {
    std::unordered_map<int, int> oreCounts = getNeighbourOres(neighbours, currentTiles, layerOres);

    int aliveCount = 0;
    Vec2i max(0, 0);
    for (auto &[ore, count] : oreCounts) {
        if (ore != 0) {
            aliveCount += count;
        }
        if (count >= config.cellsForBirth) {
            return ore;
        }
        if (count >= config.overpopulationCount) {
            return 0;
        }
        if (count > max.y) {
            max = {ore, count};
        }
    }

    return cell;
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

int Terrain::getTileIndex(const int x, const int y) const{
    return x+(-y*config.width);
}

void Terrain::mineBlock(const int x, const int y) {
    int index = getTileIndex(x,y);
    tiles[index] = 3;
}


int Terrain::getRandomOre(const std::unordered_map<int,double> &layerOres,const int x, const int y, const int layerDepth, const int layerWidth) { //only works for sets with a total of 100
    const siv::PerlinNoise::seed_type seed = 123456u;
    const siv::PerlinNoise perlin{seed};
    const double xPos = double(x)/double(layerWidth);
    const double yPos = double(y)/double(layerDepth);
    std::cout << "X position: " << xPos << " Y position: " << yPos << "\n";
    const double noise = perlin.normalizedOctave2D_01(xPos*10000, yPos*10000,3);
    
    std::cout << std::to_string(noise)  << "\n";
//    int randomInt = getRandomInt(1, 100);
    double total = 0;
    for (auto &[ore,percentageChance]:layerOres) {
        total += percentageChance;
        if (noise <= total) {
            return ore;
        }
    }
    std::cout << "FAILED TO SELECT AN ORE" << "\n";
    return 0;
}

void Terrain::generateLayer() {
    int layerDepth = 50;
    std::vector<int> layerTiles {};
    for (int i = 0; i < layerDepth; i++) {
        for (int j = 0; j < config.width; j++) {
            if (j == 0 || j == config.width-1) {
                layerTiles.push_back(7);
            } else {
                int cell = getRandomOre(config.layerInfo[0],j,i,layerDepth,config.width);
                layerTiles.push_back(cell);
        
            }
        }
    }
    
    for (int i = 0; i < config.turnCount; i++) {
        layerTiles = simulateTurn(layerTiles,layerDepth,config.layerInfo[0]);
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
            if ( j == config.width-1 || i == 0) {
                tiles.push_back(7);
            } else {
                tiles.push_back(3);
            }
        }
    }
    height = startingHeight;
    generateBuffer();
}
