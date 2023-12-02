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


const float * Matrix3::getFloatArray() const {
    return &matrix_Array[0];
};

//creates ortho matrix - translations not neccesary in 2d context
Matrix3::Matrix3(float left, float right, float bottom, float top) {
    matrix_Array = {
        2.0f/(right-left), 0.0f, 1.0f*-((right+left)/(right-left)),
        0.0f, 2.0f/(top-bottom), 1.0f*-((top+bottom)/(top-bottom)),
        0.0f, 0.0f, 1.0f
    };
};

Matrix3::Matrix3() { //initialises zero matrix
    matrix_Array = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
};
Matrix3::Matrix3(float v) { //creates multiplication by v of identity matrix
    matrix_Array = {
        v,0.0f,0.0f,
        0.0f,v,0.0f,
        0.0f,0.0f,v
    };
};
// Construct 3x3 matrix with per element inputs
Matrix3::Matrix3(
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
// Construct 3x3 matrix from another std::array
Matrix3::Matrix3(const std::array<float,9>& array) {
    matrix_Array = array;
}

//renders matrix in form
/*
 | a b c |
 | d e f |
 | g h i |
 */
Matrix3::operator std::string() const {
    std::stringstream stream;
    for (int i = 0; i < 9; i += 3) {
        stream << "|" << matrix_Array[i] << " " << matrix_Array[i+1] << " " << matrix_Array[i+2] << "|\n";
    }
    return stream.str();
}

//adds to std::arrays together and returns new matrix object
Matrix3 Matrix3::operator+(const Matrix3& other) const {
    return Matrix3(
        matrix_Array[0] + other.matrix_Array[0], matrix_Array[1] + other.matrix_Array[1], matrix_Array[2] + other.matrix_Array[2],
        matrix_Array[3] + other.matrix_Array[3], matrix_Array[4] + other.matrix_Array[4], matrix_Array[5] + other.matrix_Array[5],
        matrix_Array[6] + other.matrix_Array[6], matrix_Array[7] + other.matrix_Array[7], matrix_Array[8] + other.matrix_Array[8]
    );
}
//subtracts two matrices and stores them in a Matrix3 object
Matrix3 Matrix3::operator-(const Matrix3& other) const {
    return Matrix3(
        matrix_Array[0] - other.matrix_Array[0], matrix_Array[1] - other.matrix_Array[1], matrix_Array[2] - other.matrix_Array[2],
        matrix_Array[3] - other.matrix_Array[3], matrix_Array[4] - other.matrix_Array[4], matrix_Array[5] - other.matrix_Array[5],
        matrix_Array[6] - other.matrix_Array[6], matrix_Array[7] - other.matrix_Array[7], matrix_Array[8] - other.matrix_Array[8]
    );
}
//adds other matrix to current matrix
void Matrix3::operator+=(const Matrix3& other) {
    for (int i = 0; i < 9; i++){
        matrix_Array[i] += other.matrix_Array[i];
    }
}
//subtracts other matrix from current matrix
void Matrix3::operator-=(const Matrix3& other) {
    for (int i = 0; i < 9; i++){
        matrix_Array[i] -= other.matrix_Array[i];
    }
}
//multiplies to matrices with scalar multiplication
Matrix3 Matrix3::operator*(float v) const {
    return Matrix3(
        matrix_Array[0] * v, matrix_Array[1] * v, matrix_Array[2] * v,
        matrix_Array[3] * v, matrix_Array[4] * v, matrix_Array[5] * v,
        matrix_Array[6] * v, matrix_Array[7] * v, matrix_Array[8] * v
    );
}
//multiplies to current matrix
void Matrix3::operator*=(float v) {
    for (int i=0; i<9; i++) {
        matrix_Array[i] *= v;
    }
}
//multiplies two matrices and returns the outcome
Matrix3 Matrix3::operator*(const Matrix3 &other) const {
    return Matrix3(
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
};
//multiplies current matrix by another
void Matrix3::operator*=(const Matrix3 &other) {
    matrix_Array[0] = matrix_Array[0] * other.matrix_Array[0] + matrix_Array[1] * other.matrix_Array[3] + matrix_Array[2] * other.matrix_Array[6];
    matrix_Array[1] = matrix_Array[0] * other.matrix_Array[1] + matrix_Array[1] * other.matrix_Array[4] + matrix_Array[2] * other.matrix_Array[7];
    matrix_Array[2] = matrix_Array[0] * other.matrix_Array[2] + matrix_Array[1] * other.matrix_Array[5] + matrix_Array[2] * other.matrix_Array[8];
    matrix_Array[3] = matrix_Array[3] * other.matrix_Array[0] + matrix_Array[4] * other.matrix_Array[3] + matrix_Array[5] * other.matrix_Array[6];
    matrix_Array[4] = matrix_Array[3] * other.matrix_Array[1] + matrix_Array[4] * other.matrix_Array[4] + matrix_Array[5] * other.matrix_Array[7];
    matrix_Array[5] = matrix_Array[3] * other.matrix_Array[2] + matrix_Array[4] * other.matrix_Array[5] + matrix_Array[5] * other.matrix_Array[8];
    matrix_Array[6] = matrix_Array[6] * other.matrix_Array[0] + matrix_Array[7] * other.matrix_Array[3] + matrix_Array[8] * other.matrix_Array[6];
    matrix_Array[7] = matrix_Array[6] * other.matrix_Array[1] + matrix_Array[7] * other.matrix_Array[4] + matrix_Array[8] * other.matrix_Array[7];
    matrix_Array[8] = matrix_Array[6] * other.matrix_Array[2] + matrix_Array[7] * other.matrix_Array[5] + matrix_Array[8] * other.matrix_Array[8];
};


// divides from current matrix
void Matrix3::operator/=(float v) {
    assert(v != 0);
    float inv_v = 1.0f / v;
    for (int i = 0; i < 9; i++) {
        matrix_Array[i] *= inv_v;
    }
}

//float division between two matrices
Matrix3 Matrix3::operator/(float v) const {
    assert(v != 0);
    float inv_v = 1.0f / v;
    return Matrix3(
        matrix_Array[0] * inv_v, matrix_Array[1] * inv_v, matrix_Array[2] * inv_v,
        matrix_Array[3] * inv_v, matrix_Array[4] * inv_v, matrix_Array[5] * inv_v,
        matrix_Array[6] * inv_v, matrix_Array[7] * inv_v, matrix_Array[8] * inv_v
    );
}

//void Matrix3::rotate(float t) {
//    matrix_Array[0] *= cos(t);
//    matrix_Array[1] *= sin(t);
//    matrix_Array[3] *= -sin(t);
//    matrix_Array[4] *= cos(t);
//}
