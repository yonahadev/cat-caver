//
//  gui.cpp
//  cat-caver
//
//  Created by tom on 2023/12/17.
//

#include "gui.hpp"
#include "quad.hpp"
#include "vertex.hpp"

void Gui::renderButton(const std::string &string, const int x, const int y, const int height, Texture &texture, Shader &shader, const int bgColour, const int textColour) {
    int width = text.generate(string,x,y);
    std::vector<Vertex> vertices;
    generateUIQuad(width, height, x, y, vertices);
    vbo = VBO();
    vao = VAO();
    vao.bindArray();
    vbo.bindBuffer();
    vbo.bindData(vertices);
    vao.enableAttributes();
    shader.loadUniform<int>(false, "u_IsTexture");
    shader.loadUniform<Vec4f>(colours[bgColour], "u_QuadColour");
    vbo.draw();
    shader.loadUniform<int>(true, "u_IsTexture");
    texture.setTexture("fontImg");
    shader.loadUniform<Vec4f>(colours[textColour], "u_QuadColour");
    text.draw();
}

int Gui::getWidth(const std::string &string) {
    //generates the text to get the width preemptively without drawing it
    return text.generate(string, 0, 0);
}

void Gui::renderText(const std::string &string, const int x, const int y, Texture &texture, Shader &shader,const int colour) {
    shader.loadUniform<int>(true, "u_IsTexture");
    texture.setTexture("fontImg");
    shader.loadUniform<Vec4f>(colours[colour], "u_QuadColour");
    text.generate(string, x, y);
    text.draw();
}
