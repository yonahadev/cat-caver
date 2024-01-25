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

class Sprite {  
public:
    float hitboxLeft;
    float hitboxRight;
    float hitboxTop;
    float hitboxBottom;
    float airborne = 0;
    void adjustHitbox();
    int textureIndex;
    bool collisionsOn;
    Mat3 matrix;
    Vec2f coordinates;
    VBO vbo;
    VAO vao;
    bool falling = false;
    std::vector<std::string> collisions;
    void generateGLQuad();
    void teleport(const float x, const float y,const std::vector<int> &blockIndices);
    void update(const std::vector<int> &blockIndices,float xPos,float yPos);
    bool getCollision(const std::string &search) const;
    virtual void checkCollisions(const std::vector<int> &blockIndices);
    void getCoordinates() const;
    void getHitbox() const;
    void getMatrix() const;
    void jump ();
    bool accelerate(const std::vector<int> &blockIndices);
    void move(const float x,const float y);
    virtual void moveSprite(const float x,const float y, const std::vector<int> &blockIndices);
    Sprite(float offsetX,float offsetY, const int textureIndex);
};

#endif /* player_hpp */
