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
#include <unordered_map>
#include "character.hpp"
#include "vertexBuffer.hpp"
#include "vertexArray.hpp"

struct TextData {
    std::vector<Character> characters;
    int displayLength;
};

class Text {
private:
    void processStream(std::ifstream &stream);
    std::ifstream readFile(const std::string &fileName);
    std::unordered_map<int,Character> charMap;
    Character getCharacter(const char character);
    VAO vao;
    VBO vbo;
public:
    void draw() const;
    TextData generateCharacters(const std::string &string,int x, int y);
    void generate(const std::string &string, int x, int y);
    Text(const std::string &fileName);
};

#endif /* text_hpp */
