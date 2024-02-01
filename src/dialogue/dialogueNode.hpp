//
//  dialogueNode.hpp
//  cat-caver
//
//  Created by tom on 2024/02/01.
//

#ifndef dialogueNode_hpp
#define dialogueNode_hpp

#include <stdio.h>
#include <string>

struct Choice {
    std::string choiceText;
    std::string nextNode;
};


struct DialogueNode {
private:
public:
    std::vector<std::string> dialogue;
    std::vector<Choice> choices;
    DialogueNode(const std::vector<std::string> &dialogue,const std::vector<Choice> &choices);
};

#endif /* dialogueNode_hpp */
