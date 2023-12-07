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
#include <regex>

const std::regex expression("([a-zA-Z]+).png");

unsigned char * Texture::loadImage(const char *filePath) {
    int width,height,channelNumber;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * textureData = stbi_load(filePath, &width, &height, &channelNumber, 0);
    imageWidth = width;
    imageHeight = height;
    stbi_image_free(textureData);
//    std::cout << "Image width: " << width << " Image height: " << height << "\n";
    return textureData;
};

void Texture::setTexture(const std::string &texture) {
    int textureID = textures[texture];
//    std::cout << "Switching to texture: " << texture << " id: " << textureID << "\n";
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    if (texture == "spritesheet") {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    } else if (texture == "fontImg") {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
};


void Texture::parseURLS(const std::vector<std::string> &urls) {
    for (const std::string &url: urls) {
        int texture;
        std::smatch matches;
        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D,texture);
        if (std::regex_search(url,matches,expression)) {
            unsigned char * textureData = loadImage(url.c_str());
            if (textureData) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,textureData);
                glGenerateMipmap(GL_TEXTURE_2D);
                std::cout << "Loading texture: " << matches[1] << " id: " << texture << "\n";
                textures[matches[1]] = texture;
                textureNames.push_back(matches[1]);
            } else {
                throw std::runtime_error("Failed to load texture data for: "+url);
            }
        } else {
            throw std::runtime_error("Invalid file name: "+url);
        };
    }
}

Texture::Texture(const std::vector<std::string> &urls) {
    parseURLS(urls);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Texture::~Texture() {
    for (const std::string &name: textureNames) {
        int textureID = textures[name];
        glDeleteBuffers(1, &textureID);
    }
}
