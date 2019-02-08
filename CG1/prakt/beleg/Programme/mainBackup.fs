#version 420 core  // 420, 330 core , compatibility
uniform vec3 Ambient; 
uniform vec3 LightColor; 
uniform vec3 LightPosition;
uniform vec3 EyeDirection; 
uniform float Shininess;
uniform mat4 MVMatrix;
// Spotlicht variablen
//uniform vec3 ConeDirection;
//uniform float ConstantAttenuation;
//uniform float LinearAttenuation;
//uniform float QuadraticAttenuation;
//uniform float SpotCosCutoff;
//uniform float SpotExponent;

vec3 ReflectionLightColor = vec3(1,1,1);
// mehrere Lichtquellen
//const int MaxLights=3;
//uniform LightProperties Lights[MaxLights];

uniform sampler2D tex;

in vec4 Color; 
in vec3 Normal;
in vec4 Position;
in vec2 vs_tex_coord;

layout(location=0) out vec4 fColor;

void main() {
    // spot licht berechnung ===
//    vec3 lightDirection=LightPosition-vec3(Position);
//    float lightDistance=length(lightDirection);
//    lightDirection=lightDirection/lightDistance;
//    
//    float attenuation=1.0 / (ConstantAttenuation + LinearAttenuation*lightDistance 
//        + QuadraticAttenuation*lightDistance*lightDistance);
//    float spotCos=dot(lightDirection,-ConeDirection);
//    if (spotCos<SpotCosCutoff) attenuation=0.0;
//    else attenuation*=pow(spotCos,SpotExponent);
    // ===

    vec3 lightDirection=normalize(LightPosition-vec3(Position));
    float diffuse=max(0.0,dot(Normal,lightDirection));
    vec3 halfVector=normalize(lightDirection+normalize(EyeDirection));
    float specular=max(0.0,dot(Normal, halfVector));

    if (diffuse==0.0) specular=0.0; 
    else specular=pow(specular,Shininess);

    vec3 scatteredLight=Ambient+LightColor*diffuse;
    vec3 reflectedLight=ReflectionLightColor*specular;
    vec3 rgb = min(Color.rgb*scatteredLight+reflectedLight,vec3(1.0));
    
    fColor=texture(tex,vs_tex_coord)*vec4(rgb,Color.a);
    
    // ===
//    for (int light=0;light<MaxLights;++light) {
//        vec3 scatteredLight +=
//            Lights[light].ambient*Material[MatIndex].ambient*attenuation+
//            Lights[light].color*Material[MatIndex].diffuse*diffuse*attenuation;
//
//        vec3 reflectedLight +=
//            Lights[light].color*Material[MatIndex].specular*specular*attenuation;
//
//        vec3 rgb = min(Material[MatIndex].emission+scatteredLight+reflectedLight, vec3(1.0));
//
//        fColor = vec4(rgb,Material[MatIndex].transparency); 
//    }
}