//
//  textureClass.hpp
//  Executable
//
//  Created by tom on 2023/10/11.
//

#ifndef textureClass_hpp
#define textureClass_hpp
#include <stdio.h>
#include <unordered_map>
#include <string>
#include "shader.hpp"

class Texture {
private:
    int imageWidth;
    int imageHeight;
    std::unordered_map<std::string, int> textures;
    std::vector<std::string> textureNames;
    unsigned char * loadImage(const char * filePath);
    void bindTextures(int program) const;
    void parseURLS(const std::vector<std::string> &urls);
public:
    void setTexture(const std::string &texture);
    Texture(const std::vector<std::string> &urls);
    Texture(Texture &other) = delete;
    Texture & operator=(Texture &other) = delete;
    Texture(Texture&& other) = delete;
    Texture& operator=(Texture&& other);
    ~Texture();
};
#endif /* textureClass_hpp */
