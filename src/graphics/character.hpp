//
//  character.hpp
//  cat-caver
//
//  Created by tom on 2023/12/06.
//

#ifndef character_hpp
#define character_hpp

#include <stdio.h>

struct Character {
    int id;
    int x;
    int y;
    int width;
    int height;
    int xOffset;
    int yOffset;
    int xAdvance;
    
    Character(int id, int x, int y, int width, int height, int xOffset, int yOffset, int xAdvance): id(id), x(x),y(y),width(width),height(height),xOffset(xOffset),yOffset(yOffset),xAdvance(xAdvance) {}
    
    Character() {}
};
#endif /* character_hpp */
