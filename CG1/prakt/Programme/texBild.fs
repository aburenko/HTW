#version 420 core  // 420, 330 core , compatibility
uniform sampler2D tex;
in vec2 vs_tex_coord;
in vec4 vs_color;
layout(location=0) out vec4 color;
void main() {
color=texture(tex,vs_tex_coord);
 }
