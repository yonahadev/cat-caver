//
//  block.hpp
//  cat-caver
//
//  Created by tom on 2023/12/14.
//

#ifndef pickaxe_hpp
#define pickaxe_hpp

#include <stdio.h>
#include <string>

struct Pickaxe {
    std::string name;
    int level;
    int power;
    int cost;
    
    bool operator==(const Pickaxe &other) const = default; //c++20 equality operator for structs
};

template<>
struct std::hash<Pickaxe>
{
    std::size_t operator()(const Pickaxe& pickaxe) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(pickaxe.name);
        return h1;
    }
};
#endif
