//
//  textureClass.hpp
//  Executable
//
//  Created by tom on 2023/10/11.
//

#ifndef textureClass_hpp
#define textureClass_hpp
#include <stdio.h>

class Texture {
private:
    int imageWidth;
    int imageHeight;
    unsigned char * loadImage(const char * filePath);
    void bindTextures(unsigned int program) const;
public:
    Texture(const char * filePath, unsigned int program);
};
#endif /* textureClass_hpp */
