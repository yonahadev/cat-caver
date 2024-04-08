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
    moltenStone,
    amethyst,
    lava,
    unknownium,
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
    {moltenStone,"moltenStone",6,8000,0,false},
    {amethyst,"sapphire",4,9000,100,false},
    {lava,"lava",4,10000,100,false},
    {unknownium,"unknownium",4,12500,5,false},
    {searchBlock,"searchBlock",1,5000,0,true},
    {tnt,"tnt",1,3500,1,true},
    {chest,"chest",1,10000,0,true}
};

const std::vector<World> worldData {
    {
        0,
        "Crust", //name
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
        "Mantle", //name
        {
            { //map of ore index to magnitude from center on height map to be generated
                {0.05,darkStone},
                {0.085,gold},
                {0.095,diamond},
                {0.105,ruby},
                {0.145,emerald},
                {0.155,tnt},
                {0.165,chest},
                {0.175,searchBlock}
            },
        }
    },
    {
        2,
        "Core", //name
        {
            { //map of ore index to magnitude from center on height map to be generated
                {0.9,moltenStone},
                {0.105,lava},
                {0.13,amethyst},
                {0.145,unknownium},
                {0.155,tnt},
                {0.165,chest},
                {0.175,searchBlock}
            },
        }
    }
};

//level -1 means you can't mine it / it isn't collideable

const std::vector<Pickaxe> pickaxeData {
    {"Wooden hammer",10,10,0},
    {"Shovel",2,3,50},
    {"Basic Drill",3,5,275},
    {"Pickaxe",4,8,550},
    {"Super shovel",5,12,1400},
    {"Jackhammer",6,16,2500},
    {"Super Drill",7,20,5000},
    {"Golden pickaxe",8,35,10000},
};

const std::vector<Backpack> backpackData {
    {"Pockets",500,0},
    {"Rucksack",15,50},
    {"Crate",35,250},
    {"Cargo load", 75, 500},
    {"Super sack", 250, 1500},
    {"Larger crate", 500, 3500},
    {"golden pockets", 1500, 10000},

};

const std::vector<Quest> questList {
    {"Talk to the shopkeeper", //base quest when you're not in one
        "Find out more about the expedition",
        {}
    },
    {"Good ol' digging",
        "Collect 3 stone blocks",
        {
            {0,3}
        },
        "MONEY 200",
        3
    },
    {"Copper collector",
        "Collect 10 copper and 10 iron",
        {
            {iron,5},
            {copper,5}
        },
        "WORLD 1",
        5
    },
    {"Mantle mongering",
        "Collect Dark stone, diamongs and gold",
        {
            {darkStone,20},
            {diamond,5},
            {gold,10}
        },
        "MONEY 1000",
        7
    },    
    {"Emerald extraction",
        "Get emeralds (and rubies)",
        {
            {emerald,15},
            {ruby,5}
        },
        "WORLD 3",
        8
    },
    {"Molten mystery",
        "Collect lava and amethyst",
        {
            {lava,20},
            {amethyst,10}
        },
        "MONEY 5000",
        10
    },
    {"Delve into the unknown",
        "Collect 20 unkownium",
        {
            {unknownium,20},
        },
        "MONEY 20000",
        11
    }
};

const std::vector<DialogueNode> dialogueList {
    {
        { //dialogue 0
        "Whiskers IV, I need to reach the earth's core, but unfortunately I lack the abiltiy to do it myself.",
        "I am going to need you to dig for me, but I will give you the neccessary tools and will reward you greatly.",
        "I'm gonna need a lot of materials to get to the next area, but,",
        "I think with your help we can do it.",
    },
        {{"Tell me more","1"},{"I will come back","EXIT"}} //choices
    },
    {
        { //dialogue 1
        "I need someone with digging expertise who is willing to risk it all for the sake of exploration.",
        "Unfortunately due to the last expedition I am both too frail and unwilling to venture into the mines again myself.",
        "As we progress, however, I will tell you everything you need to know so you can complete this mission successfully.",
    },
        {{"What is my first quest?","QUEST 1"},{"I will come back","EXIT"},{"I have what you asked for","QUEST COMPLETE"},{"Let me buy stuff","SHOP"}} //choices
    },
    {
        { //dialogue 2
        "You have not finished the quest yet - please get more stuff"
    },
        {{"Exit","EXIT"},{"I have what you asked for","QUEST COMPLETE"},{"Let me buy stuff","SHOP"}} //choices
    },
    {
        { //dialogue 3
        "Well done for collecting all that stuff for me - this should enable us to begin investigating what we find here."
        "I've given you an extra 200 to spend to try and help for your next quest.",
        "Go back down into the mine and collect me some more ores, and I will show you the way forward."
        },
        {{"Exit","EXIT"},{"Sure thing boss","QUEST 2"},{"I have what you asked for","QUEST COMPLETE"},{"Let me buy stuff","SHOP"}} //choices
    },
    {
        { //dialogue 4
        "Brilliant, that should be enough from this layer and now we can get you to the next world - try heading to the teleport menu and travelling to the next world.",
        "Also, once you're down there I've got another quest for you."
        },
        {{"Exit","EXIT"},{"Cheers what is my quest?","5"},{"Let me buy stuff","SHOP"}} //choices
    },
    {
        { //dialogue 5
            "Hmm it appears we have a bit of a problem, the ores in the mantle are very valuable but challenging to mine and might take a while",
            "Oh well, that doesn't matter we have time. Please collect me some dark stone, gold and diamonds."
        },
        {{"Exit","EXIT"},{"Ok I will do so","QUEST 3"},{"Let me buy stuff","SHOP"},{"I have what you asked for","QUEST COMPLETE"}} //choices
    },
    {
        { //dialogue 6
            "Hmm it appears we have a bit of a problem, the ores in the mantle are very valuable but challenging to mine and might take a while",
            "Oh well, that doesn't matter we have time. Please collect me some dark stone, gold and diamonds."
        },
        {{"Exit","EXIT"},{"Ok I will do so","QUEST 3"},{"Let me buy stuff","SHOP"},{"I have what you asked for","QUEST COMPLETE"}} //choices
    },
    {
        { //dialogue 7
            "Great, that brings us halfway there - now for the major issue, the rarer ores in the mantle.",
            "In the last expedition these presented quite the challenge, along with taking out half the team just trying to obtain them, and I myself sustained countless injuries.",
            "You, however, may have what it takes, I have given you 1000 to spend, please do all that you need to prepare to get the rubies and emeralds."
        },
        {{"Exit","EXIT"},{"I will try my best","QUEST 4"},{"Let me buy stuff","SHOP"},{"I have the stuff","QUEST COMPLETE"}} //choices
    },
    {
        { //dialogue 8
            "Fantastic, that is all the rest I needed from the mantle, you can now go onto the core of the earth.",
            "This is where things get a bit peculiar, but I will explain more once we're there so please, go on ahead.",
        },
        {{"Exit","EXIT"},{"I'm at the core","9"},{"Let me buy stuff","SHOP"}} //choices
    },
    {
        { //dialogue 9
            "Now that we're at the core, a few things remain to be investigated, we're in uncharted territories here.",
            "The only slightly documented ores I'm aware of are amethyst and lava, so lets try and get some of that to further inspect.",
            "This might take a while, but once you get that this will open up a lot of opportunities for us."
        },
        {{"Exit","EXIT"},{"Lets go for it","QUEST 5"},{"Let me buy stuff","SHOP"},{"I have what you asked for","QUEST COMPLETE"}} //choices
    },
    {
        { //dialogue 10
            "Perfect, that will be very useful to study to the point where I don't think anyone has before.",
            "I only have one remaining quest left for you to complete I'm afraid, but this will be quite the quest.",
            "There remains an ore that we have only heard of, let alone have ever seen with our own eyes, and those that may have done are no longer with us.",
            "Please go down to mine again and collect 20 unkownium, if you find any at all."
        },
        {{"Exit","EXIT"},{"What even is that?","QUEST 6"},{"Let me buy stuff","SHOP"},{"I have what you asked for","QUEST COMPLETE"}} //choices
    },
    {
        { //dialogue 11
            "Hmm interesting, it actually exists eh?",
            "I wasn't expecting that but new suprises come to us in times of hardship I suppose, if one might even call this a suprise?",
            "There are still many things that remian unknown to you, my friend. What I will say is if you keep digging you may eventually find out more.",
            "I will be here for a while, feel free to stay and mine. Who knows, you might find out something more."
        },
        {{"Thanks I guess?","EXIT"},{"Let me buy stuff","SHOP"}} //choices
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
