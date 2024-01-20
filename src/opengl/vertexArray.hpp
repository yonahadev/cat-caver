//
//  vertexArray.hpp
//  cat-caver
//
//  Created by tom on 2023/12/13.
//

#ifndef vertexArray_hpp
#define vertexArray_hpp

#include <stdio.h>

class VAO {
private:
    int ID;
public:
    void bindArray() const;
    void unbindArray() const;
    void enableAttributes() const;
    void genArrays();
    VAO();
    ~VAO();
    VAO(VAO &other) = delete;
    VAO& operator=(VAO &other) = delete;
    VAO(VAO &&other) noexcept;
    VAO& operator=(VAO &&other) noexcept;
};
#endif /* vertexArray_hpp */
