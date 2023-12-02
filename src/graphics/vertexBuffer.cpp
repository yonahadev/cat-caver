//
//  vertexBufferClass.cpp
//  Executable
//
//  Created by tom on 2023/10/13.
//

#include "vertexBuffer.hpp"
#include "glad/glad.h"

void VertexBuffer::bindArray() const {
    glBindVertexArray(VAO);
};

void VertexBuffer::unbindArray() const {
    glBindVertexArray(0);
};

void VertexBuffer::draw() const {
    bindArray();
    glDrawArrays(GL_TRIANGLES,0,numberOfVertices);
};

void VertexBuffer::bindBuffer(std::vector<Vertex> vertices) const {
    bindArray();
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
    glGenBuffers(1,&VBO);
    bindArray();
    bindBuffer(vertices);
};

VertexBuffer::VertexBuffer() {};
