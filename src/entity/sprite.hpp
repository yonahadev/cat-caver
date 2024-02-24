//
//  sprite.hpp
//  cat-caver
//
//  Created by tom on 2024/01/06.
//s

#ifndef sprite_hpp
#define sprite_hpp

#include <stdio.h>
#include "mat3.hpp"
#include "vertexBuffer.hpp"
#include "vertexArray.hpp"
#include "vec2.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include "constants.hpp"

struct Hitbox {
    float left;
    float right;
    float top;
    float bottom;
};

struct Collisions {
    bool left;
    bool right;
    bool top;
    bool bottom;
};

class Sprite {
public:
    Hitbox hitbox;
    Collisions collisions;
    float airborne = 0;
    int textureIndex;
    bool collisionsOn;
    Mat3 matrix;
    Vec2f coordinates;
    VBO vbo;
    VAO vao;
    Hitbox calculateHitbox(const Vec2f &coordinates);
    void generateGLQuad();
    void teleport(float x, float y,const std::vector<int> &blockIndices);
    virtual void checkCollisions(const std::vector<int> &blockIndices,const Hitbox &hitbox);
    bool accelerate(const std::vector<int> &blockIndices);
    void move(float x,float y);
    void moveSprite(float x,float y, const std::vector<int> &blockIndices);
    Sprite(float offsetX,float offsetY, int textureIndex);
};

#endif /* player_hpp */
