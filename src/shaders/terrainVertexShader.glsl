#version 410 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in mat3 instanceMatrix;
layout (location = 4) in int textureIndex;

uniform float texels[20]; //only x coords

uniform mat3 u_Transformation;

vec2 texCoords;
out vec2 v_TexCoords;

void main() {
    
    float f_textureIndex = float(textureIndex);
    
    float textureStart = texels[textureIndex*2];
    float textureEnd = texels[(textureIndex*2)+1];
    
    switch (gl_VertexID) {
        case 0: // 0,0 coords
        case 3:
            texCoords = vec2(textureStart,0.0f);
            break;
        case 1: // 1,0
            texCoords = vec2(textureEnd,0.0f);
            break;
        case 2:
        case 4: // 1,1
            texCoords = vec2(textureEnd,1.0f);
            break;
        case 5: // 0,1
            texCoords = vec2(textureStart,1.0f);
            break;
    }
   
    float xPos = float(aPos.x);
    float yPos = float(aPos.y);
    
    vec3 prePosition = u_Transformation * instanceMatrix * vec3(aPos.x,aPos.y,1.0);
    gl_Position = vec4(prePosition.x,prePosition.y,0.0,1.0);
    v_TexCoords = texCoords;
}

