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
#include "vertexArray.hpp"
#include "vec2.hpp"
#include "terrainConfig.hpp"
#include "block.hpp"
#include <map>
#include "tile.hpp"

class Terrain {
private:
    void generateTerrain();
    int calculateCellState(const std::vector <Vec2i> &neighbours, const unsigned int cell,const std::vector<int> &currentTiles,const std::map<int,double> &layerOres) const;
    int getPositionInTiles(const unsigned int x, const unsigned int y) const;
    std::unordered_map<int, int> getNeighbourOres(const std::vector <Vec2i> &neighbours,const std::vector<int> &currentTiles, const std::map<int,double> &layerOres) const;
    int getRandomOre(const std::map<int,double> &layerOres,const int x, const int y, const int layerDepth, const int layerWidth);
public:
    std::vector<Vec2i> getNeighbours(const int x, const int y) const;
    const TerrainConfig config;
    VAO vao;
    VBO vertexVBO;
    VBO matrixVBO;
    VBO texelsVBO;
    VAO backgroundVAO;
    VBO backgroundVBO;
    int height;
    int layerCount;
    int instanceCount;
    std::vector<Tile> tiles;
    std::vector<Block> triggerExplosion(int x,int y);
    std::vector<Block> blockData;
    std::vector<int> getRawBlockIndices() const;
    int getTile(int x,int y) const;
    int getTileIndex(int x,int y) const;
    void mineBlock(int x,int y);
    void generateBuffer(int depth);
    void generateLayer(int depth);
    Terrain(const TerrainConfig &config,const std::vector<Block> &blockData);
};
#endif /* terrainClass_hpp */
