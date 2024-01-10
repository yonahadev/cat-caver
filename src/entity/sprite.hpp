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
#include "terrain.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class Sprite {  
public:
    float hitboxLeft;
    float hitboxRight;
    float hitboxTop;
    float hitboxBottom;
    float airborne = 0;
    void adjustHitbox();
    bool collisionsOn;
    Mat3 matrix;
    Vec2f coordinates;
    VBO vbo;
    VAO vao;
    std::vector<std::string> collisions;
    void teleport(const float x, const float y,const Terrain &terrain);
    void update(const Terrain &terrain,float xPos,float yPos);
    bool getCollision(const std::string &search) const;
    void checkCollisions(const Terrain &terrain);
    void getCoordinates() const;
    void getHitbox() const;
    void getMatrix() const;
    void jump ();
    void accelerate(const Terrain &terrain);
    void move(const float x,const float y);
    virtual void moveSprite(const float x,const float y, const Terrain &dungeon);
    Sprite(float offsetX,float offsetY, const int textureIndex);
};

#endif /* player_hpp */
