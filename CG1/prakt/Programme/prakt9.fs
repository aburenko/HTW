
#version 420 core  // 420, 330 core , compatibility
uniform vec3 Ambient;
in vec4 Color;
layout(location=0) out vec4 fColor;
void main() {
 vec3 rgb= min(Color.rgb*Ambient, vec3(1.0));
 fColor=vec4(rgb, Color.a);
// fColor = Color; 
 }
