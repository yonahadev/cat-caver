//
//  quest.hpp
//  cat-caver
//
//  Created by tom on 2024/02/02.
//

#ifndef quest_hpp
#define quest_hpp

#include <stdio.h>
#include <string>
#include <map>

struct Quest {
    std::string title;
    std::string description;
    int moneyRequirement;
    std::map<int,int> blockRequirements;
};

#endif /* quest_hpp */
