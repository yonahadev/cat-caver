#version 410 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 a_TexCoords;

uniform int u_IsTexture;

uniform mat3 u_Transformation;

uniform vec4 u_QuadColour;

out vec2 v_TexCoords;

flat out int v_IsTexture;

out vec4 v_QuadColour;

vec3 prePosition;

void main() {
    prePosition = u_Transformation * vec3(aPos.x,aPos.y,1.0);
    gl_Position = vec4(prePosition.x,prePosition.y,0.0,1.0);
    v_TexCoords = a_TexCoords;
    v_IsTexture = u_IsTexture;
    v_QuadColour = u_QuadColour;
}
