//
//  layerClass.cpp
//  Executable
//
//  Created by tom on 2023/11/08.
//

#include "layer.hpp"

Layer::Layer(const std::vector<Vertex> &vertices, const std::vector<int> &tiles): buffer(vertices),tiles(tiles) {};
