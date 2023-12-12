//
//  vertexBufferClass.cpp
//  Executable
//
//  Created by tom on 2023/10/13.
//

#include "vertexBuffer.hpp"
#include "glad/glad.h"
#include <iostream>

void VertexBuffer::bindArray() const {
    glBindVertexArray(VAO);
};

void VertexBuffer::unbindArray() const {
    glBindVertexArray(0);
};

void VertexBuffer::draw() const {
    bindArray();
    glDrawArrays(GL_TRIANGLES,0,numberOfVertices);
    unbindArray();
};

void VertexBuffer::bindBuffer(std::vector<Vertex> vertices) const {
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,numberOfVertices * 4 * sizeof(float),vertices.data(),GL_DYNAMIC_DRAW);
    //position coords
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 4 * sizeof(float), (void*)0);
    //texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

VertexBuffer::VertexBuffer(std::vector<Vertex> vertices) {
    numberOfVertices = static_cast<int>(vertices.size());
    glGenVertexArrays(1,&VAO);
    bindArray();
    glGenBuffers(1,&VBO);
    bindBuffer(vertices);
    unbindArray();
};

VertexBuffer::VertexBuffer() {};

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1,&VAO);
    glDeleteBuffers(1,&VBO);
};

//move constructor
VertexBuffer::VertexBuffer(VertexBuffer&& other): VBO(other.VBO), VAO(other.VAO), numberOfVertices(other.numberOfVertices) {
    other.VAO = 0;
    other.VBO = 0;
    other.numberOfVertices = 0;
};

//move assignment
VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) {
    if (this != &other)
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
        
        std::swap(VBO, other.VBO);
        std::swap(VAO, other.VAO);
        numberOfVertices = other.numberOfVertices;
    }
    return *this;
}

