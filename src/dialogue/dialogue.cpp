//
//  dialogue.cpp
//  cat-caver
//
//  Created by tom on 2024/02/01.
//

#include "dialogue.hpp"
#include "constants.hpp"

void Dialogue::setDialogue(int nodeIndex) {
    currentNode = dialogueList[nodeIndex];
    currentLine = 0;
    lineCount = static_cast<int>(currentNode.dialogue.size());
}

Dialogue::Dialogue(): currentNode(dialogueList[0]) {}
