//
//  gui.cpp
//  cat-caver
//
//  Created by tom on 2023/12/17.
//

#include "gui.hpp"
#include "quad.hpp"
#include "vertex.hpp"
#include "constants.hpp"
#include <iostream>

void GUI::renderButton(const Button &button, Texture &texture, Shader &shader) {
    text.generate(button.text,button.x,button.y);
    renderQuad(button.x,button.y,button.width,button.height, texture, shader, button.bgColour,false,1);
    shader.loadUniform<int>(true, "u_IsTexture");
    texture.setTexture("fontImg");
    shader.loadUniform<Vec4f>(colourVector[button.textColour], "u_QuadColour");
    text.draw();
}

void GUI::renderQuad(int x, int y, int width, int height, Texture &texture, Shader &shader, int bgColour,bool isTexture, int textureIndex) {
    std::vector<Vertex> vertices;
    generateUIQuad(width, height, x, y, vertices,textureIndex);
    vao.genArrays();
    vbo.genBuffer();
    vao.bindArray();
    vbo.bindBuffer();
    vbo.bindData(vertices);
    vao.enableAttributes();
    shader.loadUniform<int>(isTexture, "u_IsTexture");
    if (isTexture) {
        texture.setTexture("spritesheet");
    }
    shader.loadUniform<Vec4f>(colourVector[bgColour], "u_QuadColour");
    vbo.draw();
}

int GUI::getWidth(const std::string &string) {
    //generates the text to get the width preemptively without drawing it
    return text.generateCharacters(string,0,0).displayLength;
}

void GUI::setVisibleButtons(const std::vector<int> &buttons) {
    for (auto &[key,value]: visibleButtons) {
        visibleButtons[key] = false;
    }
    for (const int &buttonSet: buttons) {
        visibleButtons[buttonSet] = true;
    }
}

void GUI::setDialogue(int dialogue) {
    currentDialogue = dialogueList[dialogue];
    currentLine = 0;
    lineCount = static_cast<int>(currentDialogue.size())-1;
    std::cout << "Setting dialogue: " << dialogue << " Final line index: " << lineCount << "\n";
}

void GUI::renderText(const std::string &string, int x, int y, Texture &texture, Shader &shader,int colour, bool multiLine, int maxWidth) {
    shader.loadUniform<int>(true, "u_IsTexture");
    texture.setTexture("fontImg");
    shader.loadUniform<Vec4f>(colourVector[colour], "u_QuadColour");
    if (multiLine) {
        std::vector<std::string> splitStrings = text.generateMultiLineText(string, maxWidth);
        int count = 0;
        for (std::string &str: splitStrings) {
            text.generate(str, x, y-(count*50));
            text.draw();
            count += 1;
        }
    } else {
        text.generate(string, x, y);
        text.draw();
    }
}
