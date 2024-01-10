//
//  sprite.cpp
//  cat-caver
//
//  Created by tom on 2024/01/06.
//

#include "sprite.hpp"
#include <iostream>
#include "vertex.hpp"
#include "quad.hpp"
#include <string>
#include "terrain.hpp"

void Sprite::getCoordinates() const{
    std::cout << "Current coordinates: " << "x: " << coordinates.x << " y: " << coordinates.y << "\n";
}
void Sprite::getHitbox() const{
    std::cout << "Current hitbox: " << "left: " <<hitboxLeft << " right: " << hitboxRight << " bottom: " <<hitboxBottom << " top: " << hitboxTop << "\n";
}

void Sprite::getMatrix() const {
    std::cout << "Current matrix:\n" << std::string(matrix) << "\n";
}

bool Sprite::getCollision(const std::string &search) const {
    for (const std::string &collision: collisions) {
        if (search == collision) {
            return true;
        }
    }
    return false;
}

void Sprite::checkCollisions(const Terrain &terrain) {
    //calculate coordinates that the Sprite is touching
    for (int y = (std::floor(hitboxBottom)); y <= (std::floor(hitboxTop)); y++ ) {
        for (int x = (std::floor(hitboxLeft)); x <= (std::floor(hitboxRight)); x++ ) {
            int currentTile = terrain.getRawBlockIndices()[terrain.getTileIndex(x, y)];
//            std::cout << x << "," << y << " Current tile: " << currentTile << "\n";
             if (currentTile != 3 && collisionsOn == true) {
                if (x > coordinates.x) {
                    collisions.push_back("right");
                }
                if (x < coordinates.x) {
                    collisions.push_back("left");

                }
                if (y > coordinates.x) {
                    collisions.push_back("top");

                }
                if (y < coordinates.x) {
                    collisions.push_back("bottom");

                }
                
            }
        }
    }
}

void Sprite::move(const float x,const float y) {
    matrix *= Mat3(1.0f,0.0f,x,
                          0.0f,1.0f,y,
                         0.0f,0.0f,1.0f);
}

void Sprite::jump() {
    if (airborne == 0.0f) {
        airborne += 80;
    }
}

void Sprite::accelerate(const Terrain &terrain) {

    
    if (getCollision("bottom") == false & airborne < 500) {
        airborne -= 2.5;
    }
    
    moveSprite(0, airborne/1000, terrain);

}

void Sprite::teleport(const float x, const float y,const Terrain &terrain) {
    Vec2f changeInPosition = {x-coordinates.x,y-coordinates.y};
    collisionsOn = false;
    moveSprite(changeInPosition.x, changeInPosition.y, terrain);
    collisionsOn = true;
}

void Sprite::moveSprite(const float x,const float y, const Terrain &terrain) {
    move(x,0);
    update(terrain, matrix.matrix_Array[2], matrix.matrix_Array[5]);
    if (collisions.size() > 0) {
        move(-x,0);
        collisions = {};
    }
    move(0,y);
    update(terrain, matrix.matrix_Array[2], matrix.matrix_Array[5]);
    if (collisions.size() > 0) {
        if (getCollision("bottom") == true) {
            airborne = 0;
        }
        move(0,-y);
    }
    update(terrain, matrix.matrix_Array[2], matrix.matrix_Array[5]);
}

void Sprite::adjustHitbox() {
    hitboxLeft = coordinates.x+0.2f;
    hitboxRight = coordinates.x+0.8f;
    hitboxTop = coordinates.y+0.8f;
    hitboxBottom = coordinates.y;
}

void Sprite::update(const Terrain &terrain,float xPos,float yPos) {
    coordinates = {xPos,yPos};
    adjustHitbox();
    checkCollisions(terrain);
}
    
Sprite::Sprite(float offsetX,float offsetY, const int textureIndex): matrix(1,0,offsetX,0,1,offsetY,0,0,1),coordinates(offsetX,offsetY) {
    collisionsOn = true;
    std::vector<Vertex> vertices;
    generateQuad(0, 0, textureIndex, vertices);
    vbo = VBO();
    vao = VAO();
    vao.bindArray();
    vbo.bindBuffer();
    vbo.bindData(vertices);
    vao.enableAttributes();
    vao.unbindArray();
}

