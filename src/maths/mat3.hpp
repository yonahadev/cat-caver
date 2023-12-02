//
//  mat3Class.hpp
//  TileMap
//
//  Created by tom on 2023/10/06.
//

#ifndef mat3Class_hpp
#define mat3Class_hpp

#include <stdio.h>
#include <array>

class Mat3 {
private:
public:
    std::array<float,9> matrix_Array;
    Mat3(float left, float right, float bottom, float top);
    Mat3();
    Mat3(float v);
    Mat3(
        float v0, float v1, float v2,
        float v3, float v4, float v5,
        float v6, float v7, float v8
    );
    const float * getFloatArray() const;
    Mat3(const std::array<float,9>& array);
    operator std::string() const;
    Mat3 operator+(const Mat3& other) const;
    void operator+=(const Mat3& other);
    Mat3 operator-(const Mat3& other) const;
    void operator-=(const Mat3& other);
    Mat3 operator*(float v) const;
    void operator*=(float v);
    Mat3 operator*(const Mat3& other) const;
    void operator*=(const Mat3 &other);
    void operator/=(float v);
    Mat3 operator/(float v) const;
    
//    void rotate(float t);
};
#endif /* mat3Class_hpp */

