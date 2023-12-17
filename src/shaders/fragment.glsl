#version 410 core
out vec4 FragColor;

in vec2 v_TexCoords;

in vec4 v_QuadColour;

in vec2 v_ScreenSize;

flat in int v_IsTexture;

flat in int v_LightRadius;

uniform sampler2D u_Sample; //texture sample bound in main

void main() {
    
    vec2 screenCenter = v_ScreenSize / 2.0;
    
    if (v_IsTexture == 0) {
        if (v_LightRadius > 0) {
            vec2 currentPixel = gl_FragCoord.xy;
            float dist = distance(screenCenter,currentPixel);
            FragColor = vec4(0.0,0.0,0.0,dist/v_LightRadius);
        } else {
            FragColor = v_QuadColour;
        }
    } else {
        vec4 textureColour = texture(u_Sample,v_TexCoords);
        if (textureColour.a < 0.2) {
            discard;
        }
        FragColor = textureColour;
    }
}
