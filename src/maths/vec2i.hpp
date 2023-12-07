//
//  vec2i.hpp
//  cat-caver
//
//  Created by tom on 2023/12/06.
//

#ifndef vec2i_hpp
#define vec2i_hpp

#include <stdio.h>
#include <sstream>

struct Vec2i {
    int x;
    int y;

    bool operator == (const Vec2i &other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator != (const Vec2i &other) const {
        return x != other.x || y != other.y;
    }
    
    Vec2i operator - (const Vec2i &other) {
        return {x-other.x,y-other.y};
    }
    
    Vec2i operator + (const Vec2i &other) {
        return {x+other.x,y+other.y};
    }
    
    operator std::string() const {
        std::stringstream stream;
        stream << x << "," << y;
        return stream.str();
    }
    
    Vec2i(int x,int y): x(x), y(y) {};
    
    Vec2i(float x, float y) {
        x = floor(x);
        y = floor(y);
    }
    
    
};


#endif /* vec2i_hpp */
