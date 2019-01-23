#version 420 core  // 420, 330 core , compatibility
uniform vec3 Ambient; 
uniform vec3 LightColor; 
uniform vec3 LightPosition;
uniform vec3 EyeDirection; 
uniform float Shininess;
vec3 ReflectionLightColor= vec3(1,1,1);

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
    vec3 reflectedLight=ReflectionLightColor*specular;

    //vec3 rgb = min(Color.rgb*scatteredLight+reflectedLight,vec3(1.0)); // with ambient
    vec3 rgb = min(Color.rgb+reflectedLight,vec3(1.0));
    fColor=vec4(rgb, Color.a); 
    //fColor=vec4(Normal, Color.a); //sergej
   // fColor=Color; //sergej
}