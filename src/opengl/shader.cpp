//
//  shaderClass.cpp
//  TileMap
//
//  Created by tom on 2023/10/03.
//

#include "glad/glad.h"
#include "shader.hpp"
#include <fstream>
#include <iostream>
#include "vec2.hpp"
#include "vec4.hpp"


Shader::Shader(const char *vertexShaderFilePath,const char *fragmentShaderFilePath) {
    configureShaderProgram(vertexShaderFilePath,fragmentShaderFilePath);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

Shader::Shader(Shader&& other): shaderProgram(other.shaderProgram) {
    other.shaderProgram = 0;
}

//move assignment
Shader& Shader::operator=(Shader&& other) {
    if (this != &other)
    {
        glDeleteProgram;
        std::swap(shaderProgram, other.shaderProgram);
    }
    return *this;
}

void Shader::bind() const {
    glUseProgram(shaderProgram);
}

void Shader::unBind() const {
    glUseProgram(0);
}

template <>
void Shader::loadUniform<Mat3>(Mat3 matrix,const std::string &uniformName) const {
    bind();
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniformMatrix3fv(uniformLocation,1,GL_TRUE,matrix.getFloatArray());
}

template <>
void Shader::loadUniform<int>(int integer,const std::string &uniformName) const {
    bind();
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform1i(uniformLocation,integer);
}
    
template <>
void Shader::loadUniform<Vec2f>(const Vec2f vector,const std::string &uniformName) const {
    bind();
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform2f(uniformLocation,vector.x,vector.y);
}

template <>
void Shader::loadUniform<Vec2i>(const Vec2i vector,const std::string &uniformName) const {
    bind();
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform2i(uniformLocation,vector.x,vector.y);
}

template <>
void Shader::loadUniform<Vec4f>(const Vec4f vector,const std::string &uniformName) const {
    bind();
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform4f(uniformLocation,vector.x,vector.y,vector.z,vector.w);
}

std::string Shader::readShaderFile(const char *filePath) const{
    std::ifstream FileObject (filePath);
    std::string fileOutput;
    std::string fileLine;
    while (std::getline(FileObject, fileLine)) {
        fileOutput.append(fileLine + "\n");
    };
    FileObject.close();
    return fileOutput;
}

int Shader::configureVertexShader(const char *filePath) const {
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string fileString = readShaderFile(filePath);
    const char* c_str = fileString.c_str();
    glShaderSource(vertexShader, 1, &c_str, nullptr);
    glCompileShader(vertexShader);
    GLsizei length;
    glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&length);
    std::vector<char> infoLog(length);
    int  success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, length, nullptr, infoLog.data());
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog.data() << "\n";
    }
    return vertexShader;
}


int Shader::configureFragmentShader(const char *filePath) const {
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fileString = readShaderFile(filePath);
    const char* c_str = fileString.c_str();
    glShaderSource(fragmentShader, 1, &c_str, nullptr);
    glCompileShader(fragmentShader);
    GLsizei length;
    glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH,&length);
    std::vector<char> infoLog(length);
    int  success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog.data());
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog.data() << "\n";
    }
    return fragmentShader;
}

void Shader::configureShaderProgram(const char *vertexShaderFilePath,const char *fragmentShaderFilePath) {
    shaderProgram = glCreateProgram();
    int vertexShader = configureVertexShader(vertexShaderFilePath);
    int fragmentShader = configureFragmentShader(fragmentShaderFilePath);
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    GLsizei length;
    glGetShaderiv(shaderProgram,GL_INFO_LOG_LENGTH,&length);
    std::vector<char> infoLog(length);
    int  success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog.data());
        std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog.data() << "\n";
    }
}
