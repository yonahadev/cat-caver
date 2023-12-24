//
//  button.hpp
//  cat-caver
//
//  Created by tom on 2023/12/18.
//

#ifndef button_hpp
#define button_hpp

#include <stdio.h>
#include <string>
#include <variant>

struct Button {
    int id;
    std::string text;
    int width;
    int height;
    int x;
    int y;
    int bgColour;
    int textColour;
    std::string metaInfo;
    
    Button(int id,std::string text, int width, int height, int x, int y, int bgColour, int textColour, std::string metaInfo):id(id),text(text),width(width),height(height),x(x),y(y),bgColour(bgColour),textColour(textColour),metaInfo(metaInfo) {}
};


#endif /* button_hpp */
