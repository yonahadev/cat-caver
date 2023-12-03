//
//  player.hpp
//  Executable
//
//  Created by tom on 2023/11/25.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "mat3.hpp"
#include "vertexBuffer.hpp"
#include "vec2.hpp"
#include "terrain.hpp"

class Player {
private:
    float hitboxLeft;
    float hitboxRight;
    float hitboxTop;
    float hitboxBottom;
    void adjustHitbox();
public:
    Mat3 matrix;
    Vec2 coordinates;
    VertexBuffer buffer;
    bool colliding;
    void update(const Terrain &terrain,float xPos,float yPos);
    void checkCollisions(const Terrain &terrain);
    void getCoordinates() const;
    void getHitbox() const;
    void getMatrix() const;
    float moveSpeed = 0.03;
    void move(const float x,const float y);
    void moveCamera(const float x,const float y, const Terrain &dungeon);
    Player(float offsetX,float offsetY, const int textureIndex);
};

#endif /* player_hpp */
