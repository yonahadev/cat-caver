#version 410 core
out vec4 FragColor;

in vec3 v_TexCoords;

uniform sampler2DArray u_Sample;

void main() {
    vec4 textureColour = texture(u_Sample,v_TexCoords);
    if (textureColour.a < 0.2) {
        discard;
    }
    FragColor = textureColour;
}

