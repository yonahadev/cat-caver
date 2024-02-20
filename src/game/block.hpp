//
//  block.hpp
//  cat-caver
//
//  Created by tom on 2023/12/14.
//

#ifndef block_hpp
#define block_hpp

#include <stdio.h>
#include <string>



struct Block {
    int textureIndex;
    std::string name;
    int level;
    int hp;
    int sellValue;
    bool isSpecial;
    
    bool operator==(const Block &other) const = default; //c++20 equality operator for structs
    
    bool operator < (const Block &other) const {
        return textureIndex < other.textureIndex;
    }
    
};

template<>
struct std::hash<Block>
{
    std::size_t operator()(const Block& block) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(block.name);
        return h1;
    }
};

#endif /* block_hpp */
