#version 330 core  // 420, 330 core , compatibility
in vec4 Color;
layout(location=0) out vec4 fColor;

uniform float posx;
uniform float posy;
float a,b,c;

void main() {
    a = 1 - 0.25*sqrt(posx*posx + posy*posy);
    b = sqrt(posx*posx);
    c = sqrt(posy*posy);
    vec4 col = vec4(Color[0]*a, Color[1]+b, Color[2]+c, 0.5);
    //vec4 col = vec4(a, b, c, 0.5);
    fColor = col;
}
