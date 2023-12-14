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
    int width;
    int startingAliveChance;
    int turnCount;
    int cellsForBirth;
    int underpopulationCount;
    int overpopulationCount;
    
    DungeonConfig() {}
};


#endif /* dungeonConfig_hpp */
