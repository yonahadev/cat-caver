#version 410 core
out vec4 FragColor;

in vec2 v_TexCoords; //text is non array texture so only has vec2 as tex coords

in vec4 v_QuadColour;

uniform sampler2D u_Sample; //texture sample bound in main

void main() {
    
    vec4 textureColour = texture(u_Sample,v_TexCoords);
    if (textureColour.a < 0.2) {
        discard;
    }
    FragColor = textureColour*v_QuadColour;
}
