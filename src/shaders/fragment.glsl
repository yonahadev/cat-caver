#version 410 core
out vec4 FragColor;

in vec2 v_TexCoords;

flat in int v_IsTexture;

uniform sampler2D u_Sample; //texture sample bound in main

void main() {
    
    if (v_IsTexture == 0) {
        FragColor = vec4(0.1, 0.21, 0.39,0.5);
    } else {
        vec4 textureColour = texture(u_Sample,v_TexCoords);
        if (textureColour.a < 0.5) {
            discard;
        }
        FragColor = textureColour;
    }
}
