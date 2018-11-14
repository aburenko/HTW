
#version 330 core  // 420, 330 core , compatibility
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

uniform float posx;
uniform float posy;

out vec4 Color;

void main(){
	//vec4 npos = vec4((vPosition[0]-posx),(vPosition[1]-posy), 0.0, 1.0);
	float d = sqrt(((vPosition[0]-posx)*(vPosition[0]-posx))+((vPosition[1]-posy)*(vPosition[1]-posy)));
	vec4 npos = vec4((vPosition[0]*d),(vPosition[1]*d), 0.0, 1.0);
	gl_Position = npos;
	Color = vColor;
}
