//
//  VBOClass.cpp
//  Executable
//
//  Created by tom on 2023/10/13.
//

#include "vertexBuffer.hpp"
#include "glad/glad.h"
#include <iostream>

void VBO::draw() const {
    glDrawArrays(GL_TRIANGLES,0,verticesCount);
}

void VBO::bindBuffer() const {
    glBindBuffer(GL_ARRAY_BUFFER,ID);
}

void VBO::bindData(const std::vector<float> &vertices, int floatsPerVertex) {
    
    int floatCount = static_cast<int>(vertices.size());
    
    verticesCount = floatCount/floatsPerVertex;
    
    std::cout << "Binding vertices count: " << verticesCount << " Total floats: " << floatCount << "\n";
    
    glBufferData(GL_ARRAY_BUFFER,floatCount * sizeof(float),vertices.data(),GL_DYNAMIC_DRAW);
}

void VBO::unbindBuffer() const {
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VBO::genBuffer() {
    glGenBuffers(1,&ID);
}

VBO::VBO() {
    ID = 0;
}

VBO::~VBO() {
    if (ID != 0) {
        glDeleteBuffers(1,&ID);
    }
}

//move constructor
VBO::VBO(VBO&& other) noexcept: ID(other.ID), verticesCount(other.verticesCount){
    ID = 0;
    verticesCount = 0;
}

//move assignment
VBO& VBO::operator=(VBO&& other) noexcept {
    if (this != &other && ID != 0)
    {
        glDeleteBuffers(1, &ID);
        ID = other.ID;
        verticesCount = other.verticesCount;
        other.ID = 0;
        other.verticesCount = 0;
    }
    return *this;
}

