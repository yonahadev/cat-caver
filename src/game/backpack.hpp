//
//  backpack.hpp
//  cat-caver
//
//  Created by tom on 2023/12/28.
//

#ifndef backpack_hpp
#define backpack_hpp

#include <stdio.h>
#include <string>

struct Backpack {
    std::string name;
    int capacity;
    int cost;
    
    bool operator==(const Backpack &other) const = default; //c++20 equality operator for structs
};

template<>
struct std::hash<Backpack>
{
    std::size_t operator()(const Backpack& Backpack) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(Backpack.name);
        return h1;
    }
};

#endif /* backpack_hpp */
