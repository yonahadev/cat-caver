//
//  world.hpp
//  cat-caver
//
//  Created by tom on 2024/01/30.
//

#ifndef world_hpp
#define world_hpp

#include <stdio.h>
#include <map>
#include <string>

struct World {
    std::string name;
    int cost;
    std::map<int,int> blockCosts;
    std::vector<std::map<int, double>> layerInfo;
};

template<>
struct std::hash<World>
{
    std::size_t operator()(const World& world) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(world.name);
        return h1;
    }
};
#endif /* world_hpp */
