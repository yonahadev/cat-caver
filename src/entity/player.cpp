//
//  player.cpp
//  Executable
//
//  Created by tom on 2023/11/25.
//

#include "player.hpp"
#include <iostream>
#include "vertex.hpp"

//void Player::getCoordinates() const{
//    std::cout << "Current coordinates: " << "x: " << coordinates.x << " y: " << coordinates.y << "\n";
//};
//void Player::getHitbox() const{
//    std::cout << "Current hitbox: " << "left: " <<hitbox.left << " right: " << hitbox.right << " bottom: " <<hitbox.bottom << " top: " << hitbox.top << "\n";
//};
//
//void Player::getMatrix() const {
//    std::cout << "Current matrix:\n" << std::string(matrix) << "\n";
//}

//void Player::checkCollisions(const CellularDungeon &dungeon) {
//    //calculate coordinates that the Player is touching
//    for (int y = (std::floor(hitbox.bottom)); y <= (std::floor(hitbox.top)); y++ ) {
//        for (int x = (std::floor(hitbox.left)); x <= (std::floor(hitbox.right)); x++ ) {
//            int currentTile = dungeon.getTile(x, y);
////            std::cout << "Coordinates: " << x << ","<< y << " currentTile: " << currentTile << "\n";
//            if (currentTile == 0) {
//                colliding = true;
//            }
//        }
//    }
//}

void Player::moveUp(float distance) {
    matrix *= Mat3(1.0f,0.0f,0.00f,
                          0.0f,1.0f,distance,
                         0.0f,0.0f,1.0f);
}
void Player::moveRight(float distance) {
    matrix *= Mat3(1.0f,0.0f,distance,
                          0.0f,1.0f,0.0f,
                         0.0f,0.0f,1.0f);
}

//void moveCamera(float x, float y, const Terrain &terrain) {
//    moveRight(matrix, -xSpeed);
//    player.update(dungeon, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
//    if (player.colliding) {
//        moveRight(matrix, xSpeed);
//        player.colliding = false;
//    }
//    moveUp(matrix, -ySpeed);
//    player.update(dungeon, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
//    if (player.colliding) {
//        moveUp(matrix, ySpeed);
//    }
//    player.update(dungeon, -matrix.matrix_Array[2], -matrix.matrix_Array[5]);
//}

void Player::adjustHitbox() {
    hitboxLeft = coordinates.x+0.2;
    hitboxRight = coordinates.x+0.8;
    hitboxTop = coordinates.y+0.8;
    hitboxBottom = coordinates.y+0.2;
};

//void Player::update(const CellularDungeon &dungeon,float xPos,float yPos) {
//    coordinates = {xPos,yPos};
//    adjustHitbox();
//    checkCollisions(dungeon);
//};
    
Player::Player(float offsetX,float offsetY, const int textureIndex): coordinates(offsetX,offsetY), hitboxLeft(), matrix(1,0,-offsetX,0,1,-offsetY,0,0,1) {
    std::vector<Vertex> vertices;
//    generateTile(0, 0, textureIndex, vertices);
    buffer = VertexBuffer(vertices);
};

