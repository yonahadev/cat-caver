//
//  constants.hpp
//  cat-caver
//
//  Created by tom on 2024/01/28.
//

#ifndef constants_hpp
#define constants_hpp

#include <stdio.h>
#include "block.hpp"
#include "pickaxe.hpp"
#include "backpack.hpp"
#include "vec4.hpp"
#include <map>

constexpr int terrainWidth = 20;
constexpr int layerDepth = 20;

constexpr int textureCount = 13.0f;
constexpr float textureMultiplier = 1.0f/textureCount;

const std::vector<std::map<int, double>> layerInfo {
    { //map of ore index to magnitude from center on height map to be generated
        {0,0.05},
        {1,0.085},
        {2,0.095},
        {4,0.105},
        {7,0.145}
    },
    {
        {0,0.05},
        {4,0.08},
        {5,0.11},
        {6,0.115},
        {7,0.135}
    }
        
};

//level -1 means you can't mine it / it isn't collideable
const std::vector<Block> blockData = {
    {"stone",1,1000,1},
    {"copper",2,1500,5},
    {"iron",2,1500,5},
    {"dirt",-1,1000,0},
    {"coal",2,1250,3},
    {"gold",3,2000,10},
    {"diamond",3,3000,50},
    {"special",3,5000,0}
};

const std::vector<Pickaxe> pickaxeData = {
    {"wooden",1,10,0},
    {"Shovel",1,3,1},
    {"bare hands",1,5,275},
    {"Fork",2,8,500}
};

const std::vector<Backpack> backpackData = {
    {"pockets",5000,0},
    {"sack",15,0},
    {"crate",35,250},
    {"fat sack", 75, 500}
};

enum colours {
    white,
    black,
    grey,
    red,
    green,
    blue
};

const std::vector<Vec4f> colourVector = {
    {1.0f,1.0f,1.0f,1.0f},
    {0.0f,0.0f,0.0f,1.0f},
    {0.3f,0.3f,0.3f,0.7f},
    {1.0f,0.0f,0.0f,0.7f},
    {0.0f,1.0f,0.0f,0.7f},
    {0.0f,0.0f,1.0f,0.7f},
};

#endif /* constants_hpp */
