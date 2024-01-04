//
//  dungeonConfig.hpp
//  TileMap
//
//  Created by tom on 2023/11/22.
//

#ifndef dungeonConfig_hpp
#define dungeonConfig_hpp

#include <stdio.h>
#include <vector>
#include <map>

struct DungeonConfig {
    int width;
    int powerupChance;
    int turnCount;
    int cellsForBirth;
    int underpopulationCount;
    int overpopulationCount;
    int layerDepth;
    std::vector<std::map<int, double>> layerInfo;
    
    DungeonConfig() {}
};


#endif /* dungeonConfig_hpp */
