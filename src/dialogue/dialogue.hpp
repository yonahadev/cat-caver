//
//  dialogue.hpp
//  cat-caver
//
//  Created by tom on 2024/02/01.
//

#ifndef dialogue_hpp
#define dialogue_hpp

#include <stdio.h>
#include "dialogueNode.hpp"

class Dialogue {
private:
public:
    void setDialogue(int node);
    DialogueNode currentNode;
    int currentLine;
    int lineCount;
    Dialogue();
};

#endif /* dialogue_hpp */
