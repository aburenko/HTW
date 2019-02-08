#version 420 core  // 420, 330 core , compatibility
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 in_tex_coord;
uniform mat4 ModelViewProjection;
out vec2 vs_tex_coord;
void main(){
	gl_Position = ModelViewProjection*vPosition;
	vs_tex_coord = in_tex_coord;
}
