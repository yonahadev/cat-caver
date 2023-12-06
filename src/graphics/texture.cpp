//
//  textureClass.cpp
//  Executable
//
//  Created by tom on 2023/10/11.
//
#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"
#include "stb_image.h"
#include "glad/glad.h"
#include <iostream>
#include <stdexcept>

unsigned char * Texture::loadImage(const char *filePath) {
    int width,height,channelNumber;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * textureData = stbi_load(filePath, &width, &height, &channelNumber, 0);
    imageWidth = width;
    imageHeight = height;
    std::cout << "Image width: " << width << " Image height: " << height << "\n";
    return textureData;
};

Texture::Texture(const char * filePath,int program) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char * textureData = loadImage(filePath);
    if (textureData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,textureData);
    } else {
        throw std::runtime_error("Failed to load texture data");
    }
//    int texture2;
//    glGenTextures(1, &texture2);
//    glBindTexture(GL_TEXTURE_2D, texture2);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureData);
}
