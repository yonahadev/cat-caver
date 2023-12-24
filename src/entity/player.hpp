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
#include "vertexArray.hpp"
#include "vec2.hpp"
#include "terrain.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include "Block.hpp"
#include "pickaxe.hpp"

class Player {
private:
    float hitboxLeft;
    float hitboxRight;
    float hitboxTop;
    float hitboxBottom;
    float airborne = 0;
    void adjustHitbox();
public:
    Pickaxe equippedPickaxe;
    bool collisionsOn;
    std::unordered_map<Block, int> blockCounts;
    std::unordered_map<Pickaxe, bool> ownedPickaxes;
    int money;
    int backpackCapacity;
    int backpackCount;
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
    void jump (const Terrain &terrain);
    void accelerate(const Terrain &terrain);
    void move(const float x,const float y);
    void moveCamera(const float x,const float y, const Terrain &dungeon);
    Player(float offsetX,float offsetY, const int textureIndex, const std::unordered_map<Block, int> &map);
};

#endif /* player_hpp */
