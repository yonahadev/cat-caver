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

unsigned char * Texture::loadImage(const char *filePath) {
    int width,height,channelNumber;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * textureData = stbi_load(filePath, &width, &height, &channelNumber, 0);
    imageWidth = width;
    imageHeight = height;
    return textureData;
};

Texture::Texture(const char * filePath,unsigned int program) {
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    unsigned char * textureData = loadImage(filePath);
    //sets how colours are sampled when scale is magnified
    //bindTextures(program);
    //passes texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,textureData);
    glEnable(GL_BLEND);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureData);
}
