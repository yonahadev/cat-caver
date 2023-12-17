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


class Gui {
private:
    Text text;
    VAO vao;
    VBO vbo;
public:
    void renderButton(const std::string &string, const int x, const int y, const int height, Texture &texture, Shader &shader);
    Gui(const std::string &fontFile): text(fontFile) {}
};

#endif /* gui_hpp */
