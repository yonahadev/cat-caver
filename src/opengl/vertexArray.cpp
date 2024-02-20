//
//  vertexArray.cpp
//  cat-caver
//
//  Created by tom on 2023/12/13.
//

#include "vertexArray.hpp"
#include "glad/glad.h"
#include <iostream>

void VAO::bindArray() const {
    glBindVertexArray(ID);
}

void VAO::unbindArray() const {
    glBindVertexArray(0);
}


void VAO::enableAttributes(int floatsPerVertex) const {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, floatsPerVertex * sizeof(float), static_cast<void*>(nullptr));
    if (floatsPerVertex > 2) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,floatsPerVertex-2,GL_FLOAT,GL_FALSE, floatsPerVertex * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
        
    }
}

void VAO::genArrays() {
    glGenVertexArrays(1,&ID);
}

VAO::VAO() {
    ID = 0;
}

VAO::~VAO() {
    if (ID != 0) {
        glDeleteVertexArrays(1,&ID);
    }
}


//move constructor
VAO::VAO(VAO&& other) noexcept: ID(other.ID) {
    other.ID = 0;
}

//move assignment
VAO& VAO::operator=(VAO&& other) noexcept {
    if (this != &other && ID != 0)
    {
        glDeleteVertexArrays(1, &ID);
        ID = other.ID;
        other.ID = 0;
    }
    return *this;
}
