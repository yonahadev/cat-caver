//
//  gui.cpp
//  cat-caver
//
//  Created by tom on 2023/12/17.
//

#include "gui.hpp"
#include "quad.hpp"
#include "vertex.hpp"

void Gui::renderButton(const std::string &string, const int x, const int y, const int height, Texture &texture, Shader &shader) {
    Vec4f whiteQuad = {1.0f,1.0f,1.0f,1.0f};
    Vec4f lightQuad = {0.0f,0.0f,0.0f,1.0f};
    Vec4f mouseQuad = {0.0, 0.0, 0.0, 0.7};
    Vec4f mouseInvalid = {1.0,0.0,0.0,0.7};
    
    int width = text.renderText(string,x,y);
    std::vector<Vertex> vertices;
    generateUIQuad(width, height, x-15, y-10, vertices);
    vbo = VBO();
    vao = VAO();
    vao.bindArray();
    vbo.bindBuffer();
    vbo.bindData(vertices);
    vao.enableAttributes();
    shader.loadUniform<int>(false, "u_IsTexture");
    shader.loadUniform<Vec4f>(mouseInvalid, "u_QuadColour");
    vbo.draw();
    shader.loadUniform<int>(true, "u_IsTexture");
    shader.loadUniform<Vec4f>(whiteQuad, "u_QuadColour");
    text.draw();
}
