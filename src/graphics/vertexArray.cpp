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


void VAO::enableAttributes() const {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 4 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
}

VAO::VAO() {
    glGenVertexArrays(1,&ID);
}

VAO::~VAO() {
    glDeleteVertexArrays(1,&ID);
}


//move constructor
VAO::VAO(VAO&& other) noexcept: ID(other.ID) {
    glDeleteVertexArrays(1,&ID);
    other.ID = 0;
}

//move assignment
VAO& VAO::operator=(VAO&& other) noexcept {
    if (this != &other)
    {
        glDeleteVertexArrays(1, &ID);
        ID = other.ID;
        other.ID = 0;
    }
    return *this;
}
