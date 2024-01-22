//
//  terrainConfig.hpp
//  TileMap
//
//  Created by tom on 2023/11/22.
//

#ifndef terrainConfig_hpp
#define terrainConfig_hpp

#include <stdio.h>
#include <vector>
#include <map>

struct TerrainConfig {
    int width;
    int powerupChance;
    int turnCount;
    int cellsForBirth;
    int underpopulationCount;
    int overpopulationCount;
    int layerDepth;
    std::vector<std::map<int, double>> layerInfo;
    
    TerrainConfig() {}
};


#endif /* terrainConfig_hpp */
