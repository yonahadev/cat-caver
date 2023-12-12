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
#include "vec2i.hpp"
#include "dungeonConfig.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;


class Terrain {
private:
    void generateTerrain();
    const DungeonConfig config;
    int calculateCellState(const std::vector <Vec2i> &neighbours, const unsigned int cell) const;
    std::vector<Vec2i> getNeighbours(const int x, const int y) const;
    int getPositionInTiles(const unsigned int x, const unsigned int y) const;
    std::vector<int> simulateTurn(const std::vector<int> &tiles, const int layerDepth);
    unsigned int getAliveNeighbourCount(const std::vector <Vec2i> &neighbours) const;
public:
    int height;
    std::vector<int> tiles;
    VertexBuffer buffer;
    json blockData;
    bool isCollideable(const int tile) const;
    int getBlockHP(const int tile) const;
    int getTile(const int x,const int y) const;
    int getTileIndex(const int x,const int y) const;
    std::string getBlockName(const int tile) const;
    void mineBlock(const int x,const int y);
    void generateBuffer();
    void generateLayer();
    Terrain(const DungeonConfig &config,const json &blockData);
};
#endif /* terrainClass_hpp */
