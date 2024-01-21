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
#include "dungeonConfig.hpp"
#include "block.hpp"
#include <map>
#include "tile.hpp"

class Terrain {
private:
    void generateTerrain();
    int calculateCellState(const std::vector <Vec2i> &neighbours, const unsigned int cell,const std::vector<int> &currentTiles,const std::map<int,double> &layerOres) const;
    int getPositionInTiles(const unsigned int x, const unsigned int y) const;
    std::vector<int> simulateTurn(const std::vector<int> &tiles, const int layerDepth, const std::map<int,double> &layerOres);
    std::unordered_map<int, int> getNeighbourOres(const std::vector <Vec2i> &neighbours,const std::vector<int> &currentTiles, const std::map<int,double> &layerOres) const;
    int getRandomOre(const std::map<int,double> &layerOres,const int x, const int y, const int layerDepth, const int layerWidth);
public:
    std::vector<Vec2i> getNeighbours(const int x, const int y) const;
    const DungeonConfig config;
    VAO vao = VAO();
    VBO vertexVBO = VBO();
    VBO matrixVBO = VBO();
    VBO texelsVBO = VBO();
    int height;
    int layerCount;
    int instanceCount;
    std::vector<Tile> tiles;
    std::vector<Block> triggerExplosion(const int x, const int y);
    std::vector<Block> blockData;
    std::vector<int> getRawBlockIndices() const;
    int getTile(const int x,const int y) const;
    int getTileIndex(const int x,const int y) const;
    void mineBlock(const int x,const int y);
    void generateBuffer();
    void generateLayer();
    Terrain(const DungeonConfig &config,const std::vector<Block> &blockData);
};
#endif /* terrainClass_hpp */
