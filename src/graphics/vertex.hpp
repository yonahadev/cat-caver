//
//  vertexStruct.hpp
//  Executable
//
//  Created by tom on 2023/10/12.
//

#ifndef vertexStruct_hpp
#define vertexStruct_hpp

#include <stdio.h>

struct Vertex {
    float x;
    float y;
    float texX;
    float texY;
    
    Vertex(float x,float y, float texX, float texY): x(x), y(y), texX(texX), texY(texY) {};
};

#endif /* vertexStruct_hpp */
