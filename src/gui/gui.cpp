//
//  gui.cpp
//  cat-caver
//
//  Created by tom on 2023/12/17.
//

#include "gui.hpp"
#include "quad.hpp"

#include "constants.hpp"
#include <iostream>

void GUI::renderButton(const Button &button, Texture &texture, Shader &quadShader, Shader &textShader) {
    text.generate(button.text,button.x,button.y);
    renderQuad(button.x,button.y,button.width,button.height, texture, quadShader, button.bgColour,false,1);
    texture.setTexture("fontImg",false);
    textShader.loadUniform<Vec4f>(colourVector[button.textColour], "u_QuadColour");
    renderText(button.text, button.x, button.y, texture, textShader, white, false, 0);
}

void GUI::renderQuad(int x, int y, int width, int height, Texture &texture, Shader &shader, int bgColour,bool isTexture, int textureIndex) {
    std::vector<float> vertices;
    generateUIQuad(width, height, x, y, vertices,textureIndex,isTexture);
    vao.genArrays();
    vbo.genBuffer();
    vao.bindArray();
    vbo.bindBuffer();
    if (isTexture) {
        vbo.bindData(vertices,5);
        vao.enableAttributes(5);
        texture.setTexture("spritesheet",true);
    } else {
        vbo.bindData(vertices,2);
        vao.enableAttributes(2);
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

int GUI::renderText(const std::string &string, int x, int y, Texture &texture, Shader &shader,int colour, bool multiLine, int maxWidth) {
    texture.setTexture("fontImg",false);
    shader.loadUniform<Vec4f>(colourVector[colour], "u_QuadColour");
    int count = 0;
    if (multiLine) {
        std::vector<std::string> splitStrings = text.generateMultiLineText(string, maxWidth);
        for (std::string &str: splitStrings) {
            text.generate(str, x, y-(count*50));
            text.draw();
            count += 1;
        }
    } else {
        text.generate(string, x, y);
        text.draw();
    }
    return count*50;
}
