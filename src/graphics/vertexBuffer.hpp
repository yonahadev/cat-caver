//
//  vertexBufferClass.hpp
//  Executable
//
//  Created by tom on 2023/10/13.
//

#ifndef vertexBufferClass_hpp
#define vertexBufferClass_hpp

#include <stdio.h>
#include <vector>
#include "vertex.hpp"

class VertexBuffer {
private:
    unsigned int VAO;
    unsigned int VBO;
    void bindBuffer(std::vector<Vertex> vertices) const;
public:
    VertexBuffer(std::vector<Vertex> vertices);
    VertexBuffer();
    int numberOfVertices;
    void unbindArray() const;
    void bindArray() const;
    void draw() const;
};

#endif /* vertexBufferClass_hpp */
