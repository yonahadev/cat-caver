//
//  vec4.hpp
//  cat-caver
//
//  Created by tom on 2023/12/17.
//

#ifndef vec4_hpp
#define vec4_hpp

#include <stdio.h>
#include <string>
#include <sstream>

template <typename T>
struct Vec4 {
    T x;
    T y;
    T z;
    T w;

//    bool operator == (const Vec4<T> &other) const {
//        return x == other.x && y == other.y;
//    }
//    
//    bool operator != (const Vec4<T> &other) const {
//        return x != other.x || y != other.y;
//    }
//    
//    Vec4<T> operator - (const Vec4<T> &other) {
//        return {x-other.x,y-other.y};
//    }
//    
//    Vec4<T> operator + (const Vec4<T> &other) {
//        return {x+other.x,y+other.y};
//    }
//    
//    Vec4<T> floor() const {
//        return {float(std::floor(x)),float(std::floor(y))};
//    }
    
    operator std::string() const {
        std::stringstream stream;
        stream << x << "," << y << z << "," << w;
        return stream.str();
    }
    
    Vec4(T x,T y, T z, T w): x(x), y(y), z(z), w(w) {}
    
//    Vec42(int x, int y) {
//        x = static_cast<float>(x);
//        y = static_cast<float>(y);
//    }
    
};

using Vec4f = Vec4<float>;
using Vec4i = Vec4<int>;

#endif /* vec4_hpp */
