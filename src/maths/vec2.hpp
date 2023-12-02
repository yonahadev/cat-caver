//
//  vec2.hpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#ifndef vec2_hpp
#define vec2_hpp

#include <stdio.h>
#include <string>
#include <sstream>

struct Vec2 {
    float x;
    float y;

    bool operator == (const Vec2 &other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator != (const Vec2 &other) const {
        return x != other.x || y != other.y;
    }
    
    Vec2 operator - (const Vec2 &other) {
        return {x-other.x,y-other.y};
    }
    
    Vec2 operator + (const Vec2 &other) {
        return {x+other.x,y+other.y};
    }
    
    Vec2 floor() const {
        return {float(std::floor(x)),float(std::floor(y))};
    }
    
    operator std::string() const {
        std::stringstream stream;
        stream << x << "," << y;
        return stream.str();
    }
    
    Vec2(float x,float y): x(x), y(y) {};
    
    
};

#endif /* vec2_hpp */
