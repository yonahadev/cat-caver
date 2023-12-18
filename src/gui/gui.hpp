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


class Gui {
private:
    Text text;
    VAO vao;
    VBO vbo;
    std::vector<Vec4f> colours;
public:
    int getWidth(const std::string &string);
    void renderButton(const std::string &string, const int x, const int y, const int height, Texture &texture, Shader &shader, const int bgColour, const int textColour);
    void renderText(const std::string &string, const int x, const int y, Texture &texture, Shader &shader,const int colour);
    Gui(const std::string &fontFile,const std::vector<Vec4f> &colours): text(fontFile),colours(colours) {}
};

#endif /* gui_hpp */

