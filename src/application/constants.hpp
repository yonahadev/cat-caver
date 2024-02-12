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
#include "dialogueNode.hpp"
#include <map>
#include "quest.hpp"

constexpr int terrainWidth = 20;
constexpr int layerDepth = 20;

constexpr int textureCount = 16.0f;
constexpr float textureMultiplier = 1.0f/textureCount;

enum sprites {
    copper,
    coal,
    gold,
    darkStone,
    diamond,
    dirt,
    stone,
    iron,
    bedrock,
    emerald,
    sapphire,
    ruby,
    tnt,
    chest,
    playerSprite,
    shopkeeperSprite
};


const std::vector<World> worldData {
    {
        "Surface Layer", //name
        {
            { //map of ore index to magnitude from center on height map to be generated
                {0.05,stone},
                {0.085,copper},
                {0.095,iron},
                {0.105,coal},
                {0.145,tnt},
                {0.155,chest}
            },
        }
    },
    {
        "Lower Surface", //name
        {
            { //map of ore index to magnitude from center on height map to be generated
                {0.05,darkStone},
                {0.085,gold},
                {0.095,diamond},
                {0.105,ruby},
                {0.145,emerald}
            },
        }
    }
};

//level -1 means you can't mine it / it isn't collideable

const std::vector<Pickaxe> pickaxeData {
    {"wooden",1,10,0},
    {"Shovel",2,3,1},
    {"bare hands",3,5,275},
    {"Fork",3,8,500}
};

const std::vector<Backpack> backpackData {
    {"pockets",3,0},
    {"sack",15,0},
    {"crate",35,250},
    {"fat sack", 75, 500}
};

const std::vector<Quest> questList {
    {"Talk to the shopkeeper",
        "See what bro has to say",
        0,
        {}
    },
    {"Good ol' digging",
        "Collect 3 stone blocks and 10 coins",
        10,
        {
            {0,3}
        }
    },
    {"Copper collector",
        "Collect 5 copper",
        0,
        {
            {1,5}
        }
    }
};

const std::vector<DialogueNode> dialogueList { //this is the max justifiable line length
    {
        { //dialogue 0
        "Welcome to cat caver - you're stuck here I'm afraid...",
        "But maybe if you help me collect what I need we can escape.",
        "I'm gonna need a lot of materials to get to the next area, but,",
        "I think with your help we can do it.",
    },
        {{"Dialogue 1","1"},{"Quest status","QUEST COMPLETE"},{"Open shop","SHOP"}} //choices
    },
    {
        { //dialogue 1
        "Well I guess I could tell you a bit about what happened here...",
        "We're the last remaning survivors on the planet but the secret lies in the earths core.",
        "As you might expect that requires a lot of digging power.",
        "So you might wanna get a better pickaxe",
    },
        {{"Give me my first quest","QUEST 1"},{"More info pls","2"},{"Cheers boss","EXIT"}} //choices
    },
    {
        { //dialogue 2
        "Go down to the mine and collect some ores",
        "Once you find enough stuff come sell it to me",
        "I'll get you hooked up with some better gear"
    },
        {{"Dialgoue 1","1"},{"side quest","QUEST 2"},{"Open shop","SHOP"}} //choices
    },
    {
        { //dialogue 2
        "You have not finished the quest yet - please get more stuff"
    },
        {{"Back","0"},{"let me out of hear","EXIT"}} //choices
    },

    
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
    menuToggles,
    tabSelector,
    pickaxeEquip,
    backpackEquip,
    dialogueButton,
    worldSelect,
    closeButton,
    dialogueChoice,
    oreSell
};


const std::vector<Block> blockData {
    {copper,"copper",2,1500,5},
    {coal,"coal",2,1250,3},
    {gold,"gold",3,2000,10},
    {darkStone,"darkStone",5,4000,2},
    {diamond,"diamond",5,4000,2},
    {dirt,"dirt",-1,1000,0},
    {stone,"stone",1,1000,1},
    {iron,"iron",2,1500,5},
    {bedrock,"bedrock",99,1500,0},
    {emerald,"emerald",4,7500,100},
    {sapphire,"sapphire",4,7500,100},
    {ruby,"ruby",4,7500,2},
    {tnt,"tnt",1,3500,1},
    {chest,"chest",1,10000,0}
};

const std::vector<Vec4f> colourVector {
    {1.0f,1.0f,1.0f,1.0f},
    {0.0f,0.0f,0.0f,1.0f},
    {0.3f,0.3f,0.3f,0.7f},
    {1.0f,0.0f,0.0f,0.7f},
    {0.0f,1.0f,0.0f,0.7f},
    {0.0f,0.0f,1.0f,0.7f},
    {1.0f,1.0f,1.0f,0.0f}
};

#endif /* constants_hpp */
