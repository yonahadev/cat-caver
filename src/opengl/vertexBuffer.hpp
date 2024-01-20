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

class VBO {
private:
    int ID;
public:
    int verticesCount;
    void bindBuffer() const;
    void unbindBuffer() const ;
    void bindData(const std::vector<Vertex> &vertices);
    void genBuffer();
    void draw() const;
    VBO();
    ~VBO();
    VBO& operator=(VBO &other) = delete;
    VBO(VBO &other) = delete;
    VBO(VBO&& other) noexcept;
    VBO& operator=(VBO&& other) noexcept;
};

#endif /* vertexBufferClass_hpp */
