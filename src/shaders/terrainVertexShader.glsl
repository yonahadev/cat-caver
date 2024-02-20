#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in mat3 instanceMatrix;
layout (location = 4) in vec3 texels;

uniform mat3 u_Transformation;

out vec3 v_TexCoords;

void main() {
    vec2 texCoords;

    switch (gl_VertexID) {
        case 0: // 0,0 coords
        case 3:
            texCoords = vec2(texels.x, 0.0);
            break;
        case 1: // 1,0
            texCoords = vec2(texels.y, 0.0);
            break;
        case 2:
        case 4: // 1,1
            texCoords = vec2(texels.y, 1.0);
            break;
        case 5: // 0,1
            texCoords = vec2(texels.x, 1.0);
            break;
    }

    float xPos = float(aPos.x);
    float yPos = float(aPos.y);

    vec3 prePosition = u_Transformation * instanceMatrix * vec3(aPos.x, aPos.y, 1.0);
    gl_Position = vec4(prePosition.x, prePosition.y, 0.0, 1.0);
    v_TexCoords = vec3(texCoords.x,texCoords.y,texels.z);
}
