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
    std::map<int,int> blockRequirements;
    std::string reward;
    int nextDialogue;
};

#endif /* quest_hpp */
