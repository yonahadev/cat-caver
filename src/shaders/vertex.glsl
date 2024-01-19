#version 410 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in mat3 a_ModelMatrix;

uniform int u_IsTexture;

uniform int u_LightRadius;

uniform mat3 u_Transformation;

uniform vec2 u_ScreenSize;

uniform vec4 u_QuadColour;

out vec2 v_TexCoords;

out vec2 v_ScreenSize;

flat out int v_IsTexture;

flat out int v_LightRadius;

out vec4 v_QuadColour;

vec3 prePosition;

void main() {
    prePosition = u_Transformation * vec3(aPos.x,aPos.y,1.0);
    gl_Position = vec4(prePosition.x,prePosition.y,0.0,1.0);
    v_TexCoords = a_TexCoords;
    v_IsTexture = u_IsTexture;
    v_LightRadius = u_LightRadius;
    v_QuadColour = u_QuadColour;
    v_ScreenSize = u_ScreenSize;
}
