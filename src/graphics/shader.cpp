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

    
Shader::Shader(const char *vertexShaderFilePath,const char *fragmentShaderFilePath) {
    configureShaderProgram(vertexShaderFilePath,fragmentShaderFilePath);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::bind() const {
    glUseProgram(shaderProgram);
}

void Shader::unBind() const {
    glUseProgram(0);
}

void Shader::loadMatrix(Mat3 matrix,const std::string &uniformName) const {
    bind();
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniformMatrix3fv(uniformLocation,1,GL_TRUE,matrix.getFloatArray());
}

void Shader::loadBool(const bool boolean,const std::string &uniformName) const {
    bind();
    int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform1i(uniformLocation,boolean);
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
    glShaderSource(vertexShader, 1, &c_str, NULL);
    glCompileShader(vertexShader);
    GLsizei length;
    glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&length);
    char* infoLog = new char[length];
    int  success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, length, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
    }
    delete[] infoLog;
    return vertexShader;
}


int Shader::configureFragmentShader(const char *filePath) const {
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fileString = readShaderFile(filePath);
    const char* c_str = fileString.c_str();
    glShaderSource(fragmentShader, 1, &c_str, NULL);
    glCompileShader(fragmentShader);
    GLsizei length;
    glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH,&length);
    char* infoLog = new char[length];
    int  success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
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
    char* infoLog = new char[length];
    int  success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << "\n";
    }
}
