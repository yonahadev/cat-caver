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
    std::vector<Vec4f> colours;
public:
    int getWidth(const std::string &string);
    void renderButton(const Button &button, Texture &texture, Shader &shader);
    void renderText(const std::string &string, const int x, const int y, Texture &texture, Shader &shader,const int colour);
    void renderQuad(const int x, const int y, const int width, const int height, Texture &texture, Shader &shader, const int bgColour);
    Gui(const std::string &fontFile,const std::vector<Vec4f> &colours): text(fontFile),vao(VAO()),vbo(VBO()),colours(colours) {}
};

#endif /* gui_hpp */

