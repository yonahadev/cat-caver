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

void Text::draw() const {
    vao.bindArray();
    vbo.draw();
}

TextData Text::generateCharacters(const std::string &string,int x, int y) {
    std::vector<Character> characters;
    int xOffset = 0;
    for (int i = 0; i < string.size(); i++) {
        const char ch = string[i];
        Character current = getCharacter(ch);
        //        std::cout << char(current.id) << " is current letter with id: " << current.id << "\n";
        //for some reason data set y offsets is not properly accounting for text offset? - manual implementation
        int yOffset = 0;
        if (ch == 'q' || ch == 'j' || ch == 'p' || ch == 'y' || ch == 'g' || ch == 'Q') {
            yOffset = -6;
        } else if (ch == '\'' || ch == '-') {
            yOffset += 18;
        } else if (ch == ' ') {
            xOffset += 2;
        }
        current.xOffset = xOffset+x;
        current.yOffset = y+yOffset;
        characters.push_back(current);
        if (i < string.size()-1) {
            xOffset += current.width+5;
        } else {
            xOffset += current.width;
        }
    }
    return {characters,xOffset};
}

std::vector<std::string> Text::generateMultiLineText(const std::string &string, int maxWidth) {
    std::vector<std::string> splitStrings;
    std::stringstream stringStream(string);
    
    std::string line;
    std::string component;
    
    int lineWidth = 0;
    while (getline(stringStream, component, ' ')) {
        int width = generateCharacters(component, 0, 0).displayLength;
        lineWidth += width;
        if (lineWidth <= maxWidth) {
            line += std::string(" ") += component;
        } else {
            splitStrings.push_back(line);
            line = component;
            lineWidth = width;
        }
    }
    splitStrings.push_back(line);
    
    
    for (std::string &str: splitStrings) {
//        std::cout << str << "\n";
    }
    
    return splitStrings;
}

void Text::generate(const std::string &string, int x, int y) {
    std::vector<Vertex> vertices;
    
    TextData textData = generateCharacters(string, x, y);
    
    for (Character &character: textData.characters) {
        generateTextQuad(character, vertices);
    }
    
    vao.genArrays();
    vbo.genBuffer();
    vao.bindArray();
    vbo.bindBuffer();
    vbo.bindData(vertices);
    vao.enableAttributes();
    vao.unbindArray();
}

Character Text::getCharacter(const char character) {
    int charIndex = int(character);
    //subtraction offsets to find right character
    
    if (charMap.find(charIndex) != charMap.end()) {
        Character charData = charMap[charIndex];
        return charData;
    } else {
        throw std::runtime_error("Failed to parse invalid character!");
    }
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
            
            charMap[currentChar.id] = currentChar;
            
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
}
