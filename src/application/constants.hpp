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

constexpr int textureCount = 17.0f;
constexpr float textureMultiplier = 1.0f/textureCount;

enum sprites {
    stone,
    darkStone,
    copper,
    iron,
    dirt,
    coal,
    gold,
    diamond,
    bedrock,
    sapphire,
    emerald,
    ruby,
    searchBlock,
    tnt,
    chest,
    playerSprite,
    shopkeeperSprite,
};

const std::vector<Block> blockData {
    {stone,"stone",1,1000,1,false},
    {darkStone,"darkStone",5,4000,2,false},
    {copper,"copper",2,1500,5,false},
    {iron,"iron",2,1500,5,false},
    {dirt,"dirt",-1,100,0,false},
    {coal,"coal",2,1250,3,false},
    {gold,"gold",3,2000,10,false},
    {diamond,"diamond",5,4000,2,false},
    {bedrock,"bedrock",99,1500,0,false},
    {sapphire,"sapphire",4,7500,100,false},
    {emerald,"emerald",4,7500,100,false},
    {ruby,"ruby",4,7500,2,false},
    {searchBlock,"searchBlock",1,5000,0,true},
    {tnt,"tnt",1,3500,1,true},
    {chest,"chest",1,10000,0,true}
};

const std::vector<World> worldData {
    {
        0,
        "Surface Layer", //name
        {
            { //map of ore index to magnitude from center on height map to be generated
                {0.05,stone},
                {0.085,copper},
                {0.095,iron},
                {0.105,coal},
                {0.145,tnt},
                {0.155,chest},
                {0.165,searchBlock}
            },
        }
    },
    {
        1,
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
    {"wooden",10,10,0},
    {"Shovel",2,3,1},
    {"bare hands",3,5,275},
    {"Fork",3,8,500}
};

const std::vector<Backpack> backpackData {
    {"pockets",500,0},
    {"sack",15,0},
    {"crate",35,250},
    {"fat sack", 75, 500}
};

const std::vector<Quest> questList {
    {"Talk to the shopkeeper",
        "Find out more about the expedition",
        {}
    },
    {"Good ol' digging",
        "Collect 3 stone blocks",
        {
            {0,3}
        },
        "WORLD 1"
    },
    {"Copper collector",
        "Collect 5 copper and 5 gold",
        {
            {copper,5},
            {gold,5}
        },
        "MONEY 100"
    }
};

const std::vector<DialogueNode> dialogueList {
    {
        { //dialogue 0
        "Welcome to cat caver - you're stuck here I'm afraid...",
        "But maybe if you help me collect what I need we can escape.",
        "I'm gonna need a lot of materials to get to the next area, but,",
        "I think with your help we can do it.",
    },
        {{"Tell me more","1"},{"Quest status","QUEST COMPLETE"},{"Open shop","SHOP"}} //choices
    },
    {
        { //dialogue 1
        "Well I guess I could tell you a bit about what happened here...",
        "We're the last remaning survivors on the planet but the secret lies in the earths core.",
        "As you might expect that requires a lot of digging power.",
        "So you might wanna get a better pickaxe",
    },
        {{"Give me my first quest","QUEST 1"},{"What should I do now?","2"},{"Cheers","EXIT"}} //choices
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
