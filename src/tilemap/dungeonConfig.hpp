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

struct DungeonConfig {
    unsigned int width;
    unsigned int startingAliveChance;
    unsigned int turnCount;
    unsigned int cellsForBirth;
    unsigned int underpopulationCount;
    unsigned int overpopulationCount;
    
    DungeonConfig() {};
};


#endif /* dungeonConfig_hpp */
