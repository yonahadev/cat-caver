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

void Texture::setTexture(const std::string &texture, bool isArrayTexture) {
    
    int textureID = textures[texture];
//    std::cout << "Switching to texture: " << texture << " id: " << textureID << "\n";

    
//            std::cout << "set texture: " << texture << "\n";
    if (isArrayTexture) {
        glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    } else {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
};


void Texture::parseURLS(const std::vector<TextureURL> &urls) {
    for (const TextureURL &url: urls) {
        int texture;
        std::smatch matches;
        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D,texture);
        if (std::regex_search(url.path,matches,expression)) {
            unsigned char * textureData = loadImage(url.path.c_str());
            if (textureData) {
                
                if (url.isArrayTexture) {
                    glTexImage3D(GL_TEXTURE_2D_ARRAY,0,GL_RGBA,imageWidth,imageWidth,imageHeight/imageWidth,0,GL_RGBA,GL_UNSIGNED_BYTE,textureData);
                    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
                } else {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,textureData);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
//                std::cout << "Loading texture: " << matches[1] << " id: " << texture << "\n";
                textures[matches[1]] = texture;
                textureNames.push_back(matches[1]);
            } else {
                throw std::runtime_error("Failed to load texture data for: "+url.path);
            }
        } else {
            throw std::runtime_error("Invalid file name: "+url.path);
        };
    }
}

Texture::Texture(const std::vector<TextureURL> &urls) {
    parseURLS(urls);
    glActiveTexture(GL_TEXTURE0);
    GL_CLAMP_TO_EDGE;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Texture::~Texture() {
    for (const std::string &name: textureNames) {
        int textureID = textures[name];
        glDeleteBuffers(1, &textureID);
    }
}

Texture::Texture(Texture&& other): textures(other.textures) {
    other.textures = {};
};

//move assignment
Texture& Texture::operator=(Texture&& other) {
    if (this != &other)
    {
        for (const std::string &name: textureNames) {
            int textureID = textures[name];
            glDeleteBuffers(1, &textureID);
        }
        std::swap(textures,other.textures);
    }
    return *this;
}
