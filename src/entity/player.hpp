//
//  player.hpp
//  Executable
//
//  Created by tom on 2023/11/25.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "vertexBuffer.hpp"
#include "vec2.hpp"
#include "mat3.hpp"
#include "terrain.hpp"

class Player {
private:
    float hitboxLeft;
    float hitboxRight;
    float hitboxTop;
    float hitboxBottom;
    bool colliding;
    void adjustHitbox();
public:
//    void update(const CellularDungeon &dungeon,float xPos,float yPos);
//    void checkCollisions(const CellularDungeon &dungeon);
//    void getCoordinates() const;
//    void getHitbox() const;
//    void getMatrix() const;
    Mat3 matrix;
    Vec2 coordinates;
    VertexBuffer buffer;
    void moveUp(float distance);
    void moveRight(float distance);
    void moveCamera(float x, float y, const Terrain &dungeon);
    Player(float offsetX,float offsetY, const int textureIndex);
};

#endif /* player_hpp */
