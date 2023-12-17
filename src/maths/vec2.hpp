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

template <typename T>
struct Vec2 {
    T x;
    T y;

    bool operator == (const Vec2<T> &other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator != (const Vec2<T> &other) const {
        return x != other.x || y != other.y;
    }
    
    Vec2<T> operator - (const Vec2<T> &other) {
        return {x-other.x,y-other.y};
    }
    
    Vec2<T> operator + (const Vec2<T> &other) {
        return {x+other.x,y+other.y};
    }
    
    Vec2<T> floor() const {
        return {float(std::floor(x)),float(std::floor(y))};
    }
    
    operator std::string() const {
        std::stringstream stream;
        stream << x << "," << y;
        return stream.str();
    }
    
    Vec2(T x,T y): x(x), y(y) {}
    
//    Vec2(int x, int y) {
//        x = static_cast<float>(x);
//        y = static_cast<float>(y);
//    }
    
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

#endif /* vec2_hpp */
