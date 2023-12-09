#version 410 core
out vec4 FragColor;

in vec2 v_TexCoords;

in vec4 v_QuadColour;

flat in int v_IsTexture;

uniform sampler2D u_Sample; //texture sample bound in main

void main() {
    
    if (v_IsTexture == 0) {
        FragColor = v_QuadColour;
    } else {
        vec4 textureColour = texture(u_Sample,v_TexCoords);
        if (textureColour.a < 0.5) {
            discard;
        }
        FragColor = textureColour;
    }
}
