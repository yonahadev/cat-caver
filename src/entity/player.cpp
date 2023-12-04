//
//  player.cpp
//  Executable
//
//  Created by tom on 2023/11/25.
//

#include "player.hpp"
#include <iostream>
#include "vertex.hpp"
#include "quad.hpp"
#include <string>

void Player::getCoordinates() const{
    std::cout << "Current coordinates: " << "x: " << coordinates.x << " y: " << coordinates.y << "\n";
};
void Player::getHitbox() const{
    std::cout << "Current hitbox: " << "left: " <<hitboxLeft << " right: " << hitboxRight << " bottom: " <<hitboxBottom << " top: " << hitboxTop << "\n";
};

void Player::getMatrix() const {
    std::cout << "Current matrix:\n" << std::string(matrix) << "\n";
}

void Player::checkCollisions(const Terrain &terrain) {
    //calculate coordinates that the Player is touching
    for (int y = (std::floor(hitboxBottom)); y <= (std::floor(hitboxTop)); y++ ) {
        for (int x = (std::floor(hitboxLeft)); x <= (std::floor(hitboxRight)); x++ ) {
            int currentTile = terrain.getTile(x, y);
//            std::cout << x << "," << y << " Current tile: " << currentTile << "\n";
            if (currentTile == 0 || currentTile == 1 || currentTile == 4) {
                colliding = true;
            }
        }
    }
}

void Player::move(const float x,const float y) {
    matrix *= Mat3(1.0f,0.0f,x,
                          0.0f,1.0f,y,
                         0.0f,0.0f,1.0f);
}

void Player::jump(const Terrain &terrain) {
    if (airborne == false) {
        airborne += 16;
        direction = "up";
    }
}

void Player::accelerate(const Terrain &terrain) {
    float frameTime = 16; //ms
    float speed = 0.016;
    if (airborne > 0) {
        airborne += frameTime;
        
        speed += airborne/2500;
        
        if (airborne > 300) {
            direction = "down";
        }
        
        if (direction == "up") {
            moveCamera(0, speed, terrain);
        } else if (direction == "down"){
            moveCamera(0, -speed/4, terrain);
        }
    }

}

void Player::moveCamera(const float x,const float y, const Terrain &terrain) {
    move(-x,0);
    update(terrain, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
    if (colliding) {
        move(x,0);
        colliding = false;
    }
    move(0,-y);
    update(terrain, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
    if (colliding) {
        airborne = 0;
        move(0,y);
    }
    update(terrain, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
}

void Player::adjustHitbox() {
    hitboxLeft = coordinates.x+0.2;
    hitboxRight = coordinates.x+0.8;
    hitboxTop = coordinates.y+0.8;
    hitboxBottom = coordinates.y+0.2;
};

void Player::update(const Terrain &terrain,float xPos,float yPos) {
    coordinates = {xPos,yPos};
    adjustHitbox();
    checkCollisions(terrain);
};
    
Player::Player(float offsetX,float offsetY, const int textureIndex): coordinates(offsetX,offsetY), hitboxLeft(), matrix(1,0,-offsetX,0,1,-offsetY,0,0,1) {
    std::vector<Vertex> vertices;
    generateQuad(0, 0, textureIndex, vertices);
    buffer = VertexBuffer(vertices);
};

