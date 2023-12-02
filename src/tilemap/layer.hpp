//
//  layerClass.hpp
//  Executable
//
//  Created by tom on 2023/11/08.
//

#ifndef layer_hpp
#define layer_hpp

#include <stdio.h>
#include <vector>
#include "vertex.hpp"
#include "vertexBuffer.hpp"

class Layer {
private:
public:
    std::vector<int> tiles;
    VertexBuffer buffer;
    Layer(const std::vector<Vertex> &vertices, const std::vector<int> &tiles);
};

#endif /* layerClass_hpp */
