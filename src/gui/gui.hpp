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


class Gui {
private:
    Text text;
    VAO vao;
    VBO vbo;
public:
    int getWidth(const std::string &string);
    void renderButton(const Button &button, Texture &texture, Shader &shader);
    void renderText(const std::string &string, int x, int y, Texture &texture, Shader &shader,int colour);
    void renderQuad(int x, int y, int width, int height, Texture &texture, Shader &shader, int bgColour, bool isTexture, int textureIndex);
    Gui(const std::string &fontFile): text(fontFile) {}
};

#endif /* gui_hpp */

