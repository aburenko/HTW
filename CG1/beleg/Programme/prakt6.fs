
#version 330 core  // 420, 330 core , compatibility
uniform sampler2D tex;
in vec4 Color;
in vec2 vs_tex_coord;
layout(location=0) out vec4 color;
void main() {
   color=Color;
 }
