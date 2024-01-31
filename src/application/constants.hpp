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
#include "world.hpp"
#include "vec4.hpp"
#include <map>

constexpr int terrainWidth = 20;
constexpr int layerDepth = 20;

constexpr int textureCount = 13.0f;
constexpr float textureMultiplier = 1.0f/textureCount;

const std::vector<World> worldData {
    {
        "Surface Layer", //name
        0, //cost
        { // block costs
            {1,1}
        },
        {
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
        }
    },
    {
        "Lower Surface", //name
        0, //cost
        { // block costs
            {1,10}
        },
        {
            { //map of ore index to magnitude from center on height map to be generated
                {0,0.05},
                {2,0.085},
                {4,0.095},
                {5,0.105},
                {6,0.145}
            },
            {
                {0,0.03},
                {4,0.08},
                {6,0.11},
                {2,0.115},
                {7,0.135}
            }
        }
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
    {"Shovel",2,3,1},
    {"bare hands",3,5,275},
    {"Fork",3,8,500}
};

const std::vector<Backpack> backpackData = {
    {"pockets",3,0},
    {"sack",15,0},
    {"crate",35,250},
    {"fat sack", 75, 500}
};

const std::vector<std::vector<std::string>> dialogueList { //this is the max justifiable line length
    {
    "Welcome to cat caver - you're stuck here I'm afraid...",
    "But maybe if you help me collect what I need we can escape.",
    "I'm gonna need a lot of materials to get to the next area, but,",
    "I think with your help we can do it.",
}
};

enum dialogues {
    startDialogue
};

enum colours {
    white,
    black,
    grey,
    red,
    green,
    blue,
    transparent
};

enum buttons {
    teleport,
    sell,
    oresAndShop,
    tabSelector,
    pickaxeEquip,
    backpackEquip,
    dialogueButton,
    worldSelect,
    closeButton
};

const std::vector<Vec4f> colourVector = {
    {1.0f,1.0f,1.0f,1.0f},
    {0.0f,0.0f,0.0f,1.0f},
    {0.3f,0.3f,0.3f,0.7f},
    {1.0f,0.0f,0.0f,0.7f},
    {0.0f,1.0f,0.0f,0.7f},
    {0.0f,0.0f,1.0f,0.7f},
    {1.0f,1.0f,1.0f,0.0f}
};

#endif /* constants_hpp */
