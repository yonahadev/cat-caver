//
//  vec2int.hpp
//  cat-caver
//
//  Created by tom on 2023/12/06.
//

#ifndef vec2int_hpp
#define vec2int_hpp

#include <stdio.h>

struct Vec2Int {
    int x;
    int y;

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
    
//    Vec2(int x, int y) {
//        x = static_cast<float>(x);
//        y = static_cast<float>(y);
//    }
    
    
};

#endif /* vec2_hpp */



#endif /* vec2int_hpp */
