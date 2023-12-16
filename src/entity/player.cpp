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
}
void Player::getHitbox() const{
    std::cout << "Current hitbox: " << "left: " <<hitboxLeft << " right: " << hitboxRight << " bottom: " <<hitboxBottom << " top: " << hitboxTop << "\n";
}

void Player::getMatrix() const {
    std::cout << "Current matrix:\n" << std::string(matrix) << "\n";
}

bool Player::getCollision(const std::string &search) const {
    for (const std::string &collision: collisions) {
        if (search == collision) {
            return true;
        }
    }
    return false;
}

void Player::checkCollisions(const Terrain &terrain) {
    //calculate coordinates that the Player is touching
    for (int y = (std::floor(hitboxBottom)); y <= (std::floor(hitboxTop)); y++ ) {
        for (int x = (std::floor(hitboxLeft)); x <= (std::floor(hitboxRight)); x++ ) {
            int currentTile = terrain.getTile(x, y);
//            std::cout << x << "," << y << " Current tile: " << currentTile << "\n";
            if (terrain.blockData[currentTile].level != -1) {
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

void Player::move(const float x,const float y) {
    matrix *= Mat3(1.0f,0.0f,x,
                          0.0f,1.0f,y,
                         0.0f,0.0f,1.0f);
}

void Player::jump(const Terrain &terrain) {
    if (airborne == 0.0f) {
        airborne += 80;
//        std::cout << "jumping" << "\n";
    }
}

void Player::accelerate(const Terrain &terrain) {

    
    if (getCollision("bottom") == false) {
        airborne -= 2.5;
    }
    
    moveCamera(0, airborne/1000, terrain);

}

void Player::moveCamera(const float x,const float y, const Terrain &terrain) {
    move(-x,0);
    update(terrain, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
    if (collisions.size() > 0) {
        move(x,0);
        collisions = {};
    }
    move(0,-y);
    update(terrain, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
    if (collisions.size() > 0) {
        if (getCollision("bottom") == true) {
            airborne = 0;
        }
        move(0,y);
    }
    update(terrain, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
}

void Player::adjustHitbox() {
    hitboxLeft = coordinates.x+0.2f;
    hitboxRight = coordinates.x+0.8f;
    hitboxTop = coordinates.y+0.8f;
    hitboxBottom = coordinates.y;
}

void Player::update(const Terrain &terrain,float xPos,float yPos) {
    coordinates = {xPos,yPos};
    adjustHitbox();
    checkCollisions(terrain);
}
    
Player::Player(float offsetX,float offsetY, const int textureIndex, const std::unordered_map<std::string, int> &map): hitboxLeft(), blockCounts(map), matrix(1,0,-offsetX,0,1,-offsetY,0,0,1),coordinates(offsetX,offsetY) {
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

