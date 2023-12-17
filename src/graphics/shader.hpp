//
//  shaderClass.hpp
//  TileMap
//
//  Created by tom on 2023/10/03.
//

#ifndef shaderClass_hpp
#define shaderClass_hpp

#include <stdio.h>
#include <string>
#include "mat3.hpp"

class Shader {
private:
    std::string readShaderFile(const char *filePath) const;
    int configureVertexShader(const char *filePath) const;
    int configureFragmentShader(const char *filePath) const;
    void configureShaderProgram(const char *vertexShaderFilePath,const char *fragmentShaderFilePath);
public:
    template <typename T>
    void loadUniform(T value, const  std::string &uniformName) const;
    int shaderProgram;
    void bind() const;
    void unBind() const;
    Shader(const char *vertexShaderFilePath,const char *fragmentShaderFilePath);
    Shader(Shader &other) = delete;
    Shader & operator=(Shader &other) = delete;
    Shader(Shader&& other);
    Shader& operator=(Shader&& other);
    ~Shader();
};
#endif /* shaderClass_hpp */
