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
#include "block.hpp"
#include <map>
#include "tile.hpp"
#include "node.hpp"

class Terrain {
private:
    void generateTerrain();
public:
    std::vector<Vec2i> path;
    int getRandomOre(int layer,int x, int y) const;
    std::vector<Vec2i> getNeighbours(int x, int y) const;
    std::vector<Node> getNeighbourNodes(const Node &startNode, const Vec2i &endPoint) const;
    void calculatePath(const Vec2i &startPoint, const Vec2i &endPoint);
    void setupWorld(int worldIndex);
    VAO vao;
    VBO vertexVBO;
    VBO matrixVBO;
    VBO texelsVBO;
    VAO backgroundVAO;
    VBO backgroundVBO;
    VAO pathVAO;
    VBO pathVBO;
    int currentWorld;
    int generatedDepth;
    int height;
    int layerCount;
    int instanceCount;
    int oreLayer;
    std::vector<Tile> tiles;
    std::vector<Block> triggerExplosion(int x,int y);
    std::vector<int> getRawBlockIndices() const;
    int getTile(int x,int y) const;
    int getTileIndex(int x,int y) const;
    void mineBlock(int x,int y);
    void generateBuffer(int depth);
    void generateLayer(int depth);
    Terrain();
};
#endif /* terrainClass_hpp */
