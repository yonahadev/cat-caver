#version 410 core
out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D u_Sample;

void main() {
    vec4 textureColour = texture(u_Sample,v_TexCoords);
    if (textureColour.a < 0.2) {
        discard;
    }
    FragColor = textureColour;
}

