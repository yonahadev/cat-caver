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
#include "layer.hpp"

class Terrain {
private:
public:
    unsigned int width;
    unsigned int height;
    std::vector<Layer> layers;
    std::vector<int> tiles;
    void generateLayer(const int offsetX, const int offsetY);
    Terrain();
};
#endif /* terrainClass_hpp */
