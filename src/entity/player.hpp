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
#include <vector>
#include <string>
#include <unordered_map>

class Player {
private:
    float hitboxLeft;
    float hitboxRight;
    float hitboxTop;
    float hitboxBottom;
    void adjustHitbox();
public:
    std::unordered_map<std::string, int> blockCounts;
    Mat3 matrix;
    Vec2 coordinates;
    VertexBuffer buffer;
    std::vector<std::string> collisions;
    void update(const Terrain &terrain,float xPos,float yPos);
    bool getCollision(const std::string &search) const;
    void checkCollisions(const Terrain &terrain);
    void getCoordinates() const;
    void getHitbox() const;
    void getMatrix() const;
    float moveSpeed = 0.03;
    float airborne = 0;
    std::string direction;
    void jump (const Terrain &terrain);
    void accelerate(const Terrain &terrain);
    void move(const float x,const float y);
    void moveCamera(const float x,const float y, const Terrain &dungeon);
    Player(float offsetX,float offsetY, const int textureIndex, const std::unordered_map<std::string, int> &map);
};

#endif /* player_hpp */
