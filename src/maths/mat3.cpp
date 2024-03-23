//
//  mat3Class.cpp
//  TileMap
//
//  Created by tom on 2023/10/06.
//

#include "mat3.hpp"
#include <iostream>
#include <sstream>
#include <assert.h>

const float * Mat3::getFloatArray() const {
    return &matrix_Array[0];
}

void Mat3::transpose(std::vector<float> &floats) {
    floats.push_back(matrix_Array[0]);
    floats.push_back(matrix_Array[3]);
    floats.push_back(matrix_Array[6]);
    floats.push_back(matrix_Array[1]);
    floats.push_back(matrix_Array[4]);
    floats.push_back(matrix_Array[7]);
    floats.push_back(matrix_Array[2]);
    floats.push_back(matrix_Array[5]);
    floats.push_back(matrix_Array[8]);
}


Mat3 Mat3::Orthographic(float left, float right, float bottom, float top) {
    
    return Mat3(
        2.0f/(right-left), 0.0f, 1.0f*-((right+left)/(right-left)),
        0.0f, 2.0f/(top-bottom), 1.0f*-((top+bottom)/(top-bottom)),
        0.0f, 0.0f, 1.0f
    );
}

Mat3::Mat3() { //initialises zero matrix
    matrix_Array = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
}
Mat3::Mat3(float v) { //creates multiplication by v of identity matrix
    matrix_Array = {
        v,0.0f,0.0f,
        0.0f,v,0.0f,
        0.0f,0.0f,v
    };
}
// Construct 3x3 matrix with per element inputs
Mat3::Mat3(
    float v0, float v1, float v2,
    float v3, float v4, float v5,
    float v6, float v7, float v8
) {
    matrix_Array = {
        v0, v1, v2,
        v3, v4, v5,
        v6, v7, v8
    };
}

Mat3::operator std::string() const {
    std::stringstream stream;
    for (int i = 0; i < 9; i += 3) {
        stream << "|" << matrix_Array[i] << " " << matrix_Array[i+1] << " " << matrix_Array[i+2] << "|\n";
    }
    return stream.str();
}


//multiplies two matrices and returns the outcome
Mat3 Mat3::operator*(const Mat3 &other) const {
    return Mat3(
        matrix_Array[0] * other.matrix_Array[0] + matrix_Array[1] * other.matrix_Array[3] + matrix_Array[2] * other.matrix_Array[6],
        matrix_Array[0] * other.matrix_Array[1] + matrix_Array[1] * other.matrix_Array[4] + matrix_Array[2] * other.matrix_Array[7],
        matrix_Array[0] * other.matrix_Array[2] + matrix_Array[1] * other.matrix_Array[5] + matrix_Array[2] * other.matrix_Array[8],
        matrix_Array[3] * other.matrix_Array[0] + matrix_Array[4] * other.matrix_Array[3] + matrix_Array[5] * other.matrix_Array[6],
        matrix_Array[3] * other.matrix_Array[1] + matrix_Array[4] * other.matrix_Array[4] + matrix_Array[5] * other.matrix_Array[7],
        matrix_Array[3] * other.matrix_Array[2] + matrix_Array[4] * other.matrix_Array[5] + matrix_Array[5] * other.matrix_Array[8],
        matrix_Array[6] * other.matrix_Array[0] + matrix_Array[7] * other.matrix_Array[3] + matrix_Array[8] * other.matrix_Array[6],
        matrix_Array[6] * other.matrix_Array[1] + matrix_Array[7] * other.matrix_Array[4] + matrix_Array[8] * other.matrix_Array[7],
        matrix_Array[6] * other.matrix_Array[2] + matrix_Array[7] * other.matrix_Array[5] + matrix_Array[8] * other.matrix_Array[8]
        );
}
//multiplies current matrix by another
void Mat3::operator*=(const Mat3 &other) {
    matrix_Array[0] = matrix_Array[0] * other.matrix_Array[0] + matrix_Array[1] * other.matrix_Array[3] + matrix_Array[2] * other.matrix_Array[6];
    matrix_Array[1] = matrix_Array[0] * other.matrix_Array[1] + matrix_Array[1] * other.matrix_Array[4] + matrix_Array[2] * other.matrix_Array[7];
    matrix_Array[2] = matrix_Array[0] * other.matrix_Array[2] + matrix_Array[1] * other.matrix_Array[5] + matrix_Array[2] * other.matrix_Array[8];
    matrix_Array[3] = matrix_Array[3] * other.matrix_Array[0] + matrix_Array[4] * other.matrix_Array[3] + matrix_Array[5] * other.matrix_Array[6];
    matrix_Array[4] = matrix_Array[3] * other.matrix_Array[1] + matrix_Array[4] * other.matrix_Array[4] + matrix_Array[5] * other.matrix_Array[7];
    matrix_Array[5] = matrix_Array[3] * other.matrix_Array[2] + matrix_Array[4] * other.matrix_Array[5] + matrix_Array[5] * other.matrix_Array[8];
    matrix_Array[6] = matrix_Array[6] * other.matrix_Array[0] + matrix_Array[7] * other.matrix_Array[3] + matrix_Array[8] * other.matrix_Array[6];
    matrix_Array[7] = matrix_Array[6] * other.matrix_Array[1] + matrix_Array[7] * other.matrix_Array[4] + matrix_Array[8] * other.matrix_Array[7];
    matrix_Array[8] = matrix_Array[6] * other.matrix_Array[2] + matrix_Array[7] * other.matrix_Array[5] + matrix_Array[8] * other.matrix_Array[8];
}
