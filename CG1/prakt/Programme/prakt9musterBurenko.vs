#version 420 core  // 420, 330 core , compatibility
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout (location=2) in vec3 VertexNormal;

uniform mat4 ModelViewProjection;
uniform mat3 NormalMatrix;
uniform mat4 MVMatrix;

out vec4 Color;
out vec3 Normal;
out vec4 Position;

void main(){
	Position=MVMatrix*vPosition;
	gl_Position = ModelViewProjection*vPosition;
	Normal=normalize(NormalMatrix*VertexNormal);
	Color = vColor;
}