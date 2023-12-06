//
//  text.cpp
//  cat-caver
//
//  Created by tom on 2023/12/06.
//

#include "text.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>
#include "quad.hpp"

const std::regex expression("id=([0-9]+)\\s+x=([0-9]+)\\s+y=([0-9]+)\\s+width=([0-9]+)\\s+height=([0-9]+)\\s+xoffset=(-?[0-9]+)\\s+yoffset=(-?[0-9]+)\\s+xadvance=([0-9]+)");


void Text::generateBuffer() {
    std::vector<Vertex> vertices;
    std::string string = "johncook";
    Character current = getCharacter(string[0]);
    std::cout << string[0] << " is current letter with id: " << current.id << "\n";
    generateTextQuad(0, 0, current, vertices);
    buffer = VertexBuffer(vertices);
}

Character Text::getCharacter(const char character) {
    int charIndex = int(character);
    //subtraction offsets to find right character
    Character charData = characterData[charIndex-36];
    return charData;
}

void Text::processStream(std::ifstream &stream) {
    
    std::smatch matches;
    std::string line;
    int count = 1;
    while (getline(stream,line)) {
        if (std::regex_search(line,matches,expression)) {
            int id = stoi(matches[1]);
            int x = stoi(matches[2]);
            int y = stoi(matches[3]);
            int width = stoi(matches[4]);
            int height = stoi(matches[5]);
            int xOffset = stoi(matches[6]);
            int yOffset = stoi(matches[7]);
            int xAdvance = stoi(matches[8]);
            
            const Character currentChar(id,x,y,width,height,xOffset,yOffset,xAdvance);
            
//            std::cout << id << "\n";
            
            characterData.push_back(currentChar);
            
        } else {
//            std::cout << "No info on line " << count << "\n";
        };
        count++;
    }
}

std::ifstream Text::readFile(const std::string &fileName) {
    std::ifstream stream(fileName);
    if (stream.fail()) {
        throw std::runtime_error("Failed to read font file");
    }
    return stream;
//    std::cout << ss.str() << "\n";
}

Text::Text(const std::string &fileName) {
    std::ifstream stream = readFile(fileName);
    processStream(stream);
    generateBuffer();
}
