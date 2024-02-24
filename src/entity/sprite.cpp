//
//  sprite.cpp
//  cat-caver
//
//  Created by tom on 2024/01/06.
//

#include "sprite.hpp"
#include <iostream>

#include "quad.hpp"
#include <string>


void Sprite::checkCollisions(const std::vector<int> &blockIndices,const Hitbox &hitbox) {
    for (int y = (std::floor(hitbox.bottom)); y <= (std::floor(hitbox.top)); y++ ) {
        for (int x = (std::floor(hitbox.left)); x <= (std::floor(hitbox.right)); x++ ) {
            
            const int currentTile = blockIndices[x+(-y*terrainWidth)];
            
             if (currentTile != dirt && collisionsOn == true) {
                 
                 collisions.right = x > coordinates.x;
                 collisions.left = x < coordinates.x;
                 collisions.top = y > coordinates.y;
                 collisions.bottom = y < coordinates.y;
                
            }
        }
    }
}

void Sprite::move(float x,float y) {
    matrix *= Mat3(1.0f,0.0f,x,
                          0.0f,1.0f,y,
                         0.0f,0.0f,1.0f);
}

bool Sprite::accelerate(const std::vector<int> &blockIndices) {
    if (collisions.bottom == false & airborne > -350) {
        airborne -= 2.5;
    }

    if (airborne != 0.0f) {
        moveSprite(0, airborne/1000, blockIndices);
    }
    
    return false;

}

void Sprite::teleport(float x, float y,const std::vector<int> &blockIndices) {
    Vec2f changeInPosition = {x-coordinates.x,y-coordinates.y};
    collisionsOn = false;
    moveSprite(changeInPosition.x, changeInPosition.y, blockIndices);
    collisionsOn = true;
}

void Sprite::moveSprite(float x,float y, const std::vector<int> &blockIndices) {
    const Vec2f updatedCoordinates = {coordinates.x+x,coordinates.y+y};
    const Hitbox updatedHitbox = calculateHitbox(updatedCoordinates);
    checkCollisions(blockIndices, updatedHitbox);
    if (collisions.left == false && collisions.right == false) {
        move(x,0);
        coordinates.x = matrix.matrix_Array[2];
    }
    if (collisions.top == false && collisions.bottom == false) {
        move(0,y);
        coordinates.y = matrix.matrix_Array[5];
    }
    if (collisions.bottom == true) {
        airborne = 0;
    }
//    std::cout << "Airborne: " << airborne << " Bottom  Collision status: " << collisions[bottom] << "\n";
}

Hitbox Sprite::calculateHitbox(const Vec2f &coordinates) {
    return {coordinates.x+0.25f,coordinates.x+0.8f,coordinates.y+0.2f,coordinates.y};
}


void Sprite::generateGLQuad() {
    std::vector<float> vertices;
    generateQuad(0, 0, textureIndex, vertices, true);
    vao.genArrays();
    vbo.genBuffer();
    vao.bindArray();
    vbo.bindBuffer();
    vbo.bindData(vertices,5);
    vao.enableAttributes(5);
    vao.unbindArray();
}

Sprite::Sprite(float offsetX,float offsetY, int textureIndex): textureIndex(textureIndex),collisionsOn(true),matrix(1,0,offsetX,0,1,offsetY,0,0,1),coordinates(offsetX,offsetY) {}

