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
#include <nlohmann/json.hpp>
using json = nlohmann::json;


class Terrain {
private:
public:
    int width;
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
    Terrain(const std::vector<int> &tiles, const int width, const int height, const json &blockData);
};
#endif /* terrainClass_hpp */
