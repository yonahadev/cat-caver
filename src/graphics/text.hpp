//
//  text.hpp
//  cat-caver
//
//  Created by tom on 2023/12/06.
//

#ifndef text_hpp
#define text_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "character.hpp"
#include "vertexBuffer.hpp"

class Text {
private:
    void processStream(std::ifstream &stream);
    std::ifstream readFile(const std::string &fileName);
    std::vector<Character> characterData;
    Character getCharacter(const char character);
    void generateBuffer();
public:
    VertexBuffer buffer;
    Text(const std::string &fileName);
};

#endif /* text_hpp */
