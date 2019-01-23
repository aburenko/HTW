#version 420 core  // 420, 330 core , compatibility
vec3 Ambient = vec3(0.1, 0.1, 0.1); 
uniform vec3 LightColor; 
uniform vec3 LightPosition;
uniform vec3 EyeDirection; 
uniform float Shininess;

in vec4 Color; 
in vec3 Normal;
out vec4 FragColor;

layout(location=0) out vec4 fColor;

void main() {
    vec3 lightDirection=LightPosition;
    float diffuse=max(0.0,dot(Normal,lightDirection));
    vec3 halfVector=normalize(lightDirection+EyeDirection);
    float specular=max(0.0,dot(Normal, halfVector));

    if (diffuse==0.0) specular=0.0; 
    else specular=pow(specular,Shininess);

    vec3 scatteredLight=Ambient+LightColor*diffuse;
    vec3 reflectedLight=LightColor*specular;

    vec3 rgb = min(Color.rgb*scatteredLight+reflectedLight,vec3(1.0));
    fColor=vec4(rgb, Color.a); 
    //fColor=vec4(Normal, Color.a); //sergej
}
