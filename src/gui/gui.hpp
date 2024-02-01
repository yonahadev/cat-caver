//
//  gui.hpp
//  cat-caver
//
//  Created by tom on 2023/12/17.
//

#ifndef gui_hpp
#define gui_hpp

#include <stdio.h>
#include <string>
#include "text.hpp"
#include "vertexBuffer.hpp"
#include "vertexArray.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vec4.hpp"
#include <vector>
#include "button.hpp"
#include <unordered_map>
#include "constants.hpp"
#include "dialogue.hpp"


class GUI {
private:
    VAO vao;
    VBO vbo;
public:
    Dialogue dialogue;
    Text text;
    bool inDialogue = false;
    std::string openMenu = "";
    std::string selectedTab = "pickaxes";
    std::string errorMessage;
    int errorTimeSet;
    int errorDuration;
    std::unordered_map<int,bool> visibleButtons;
    int getWidth(const std::string &string);
    void renderButton(const Button &button, Texture &texture, Shader &shader);
    void setVisibleButtons(const std::vector<int> &buttons);
    void renderText(const std::string &string, int x, int y, Texture &texture, Shader &shader,int colour, bool multiLine, int maxWidth);
    void renderQuad(int x, int y, int width, int height, Texture &texture, Shader &shader, int bgColour, bool isTexture, int textureIndex);
    GUI(const std::string &fontFile): text(fontFile) {}
};

#endif /* gui_hpp */

