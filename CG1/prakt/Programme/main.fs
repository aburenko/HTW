#version 330 core  // 420, 330 core , compatibility

struct LightProperties {
    bool isEnabled; bool isAmb; bool isSpot; vec3 ambient; vec3 color;
    vec3 position; vec3 coneDirection; float spotCosCutoff; float spotExponent;
    float constantAttenuation; float linearAttenuation; float quadraticAttenuation;
};

struct MaterialProperties {
    vec3 emission; vec3 ambient; vec3 diffuse; vec3 specular;
    float shininess; float transparency;
};

vec3 EyeDirection = vec3(10, 0, 0);
vec3 ReflectionLightColor = vec3(1,1,1);
float SpotExponent = 0;

// mehrere Lichtquellen
const int MaxLights=3;
const int NumMaterials=1;

LightProperties Lights[MaxLights] = {
// Ambient
            { true, true, false, vec3(0,0,0), vec3(1,1,1),
               vec3(4, 4.0, 4.0), vec3(1, 1.0, 1.0), 180, 0,
               1,0,0  },
// Richtungslicht
            { false, false, false, vec3(0,0,0), vec3(1,1,1),
               vec3(4, 4.0, 4.0), vec3(1, 1.0, 1.0), 180, 0,
               1,0,0  },
// Spotlicht
            { false, false, true, vec3(0, 0, 0), vec3(1,1,1),
               vec3(0, 5.0, 6.0), vec3(0, 0, -1), 30, 0,
               1,0,0 }
};

// Materials
MaterialProperties Material[NumMaterials] = {
    { vec3(0,0,0), vec3(0.2,0.2,0.2), vec3(0.8, 0.8, 0.8), vec3(0,0,0),
                200.0, 1}
};



uniform sampler2D tex;

in vec4 Color; 
in vec3 Normal;
in vec4 Position;
in vec2 vs_tex_coord;

layout(location=0) out vec4 fColor;

void main() {
    vec3 scatteredLight = vec3(0,0,0);
    vec3 reflectedLight = vec3(0,0,0);
    
    int MatIndex = 0;

    for (int light=0; light < MaxLights; light++) {
        if(Lights[light].isEnabled) {
            if(Lights[light].isAmb) {
                scatteredLight += Lights[light].ambient;
            }
            else if (Lights[light].isSpot) { 
                vec3 lightDirection=Lights[light].position-vec3(Position);
                float lightDistance=length(lightDirection);
                lightDirection=lightDirection/lightDistance;
                float attenuation=1.0/(Lights[light].constantAttenuation+Lights[light].linearAttenuation
                    *lightDistance
                    +Lights[light].quadraticAttenuation*lightDistance*lightDistance);
                float spotCos=dot(lightDirection,-Lights[light].coneDirection);

                if (spotCos>Lights[light].spotCosCutoff) attenuation=0.0;
                else attenuation*=pow(spotCos,SpotExponent);

                vec3 halfVector=normalize(lightDirection+EyeDirection);

                float diffuse=max(0.0,dot(Normal,lightDirection));
                float specular=max(0.0,dot(Normal,halfVector));

                if(diffuse==0.0) specular=0.0;
                else specular=pow(specular,Material[MatIndex].shininess);

                scatteredLight += Lights[light].ambient+Lights[light].color*diffuse*attenuation;
                reflectedLight += specular*Lights[light].color*attenuation;
               
            }
            else {
                vec3 lightDirection=normalize(Lights[light].position-vec3(Position));
                float diffuse=max(0.0,dot(Normal,lightDirection));
                vec3 halfVector=normalize(lightDirection+normalize(EyeDirection));
                float specular=max(0.0,dot(Normal, halfVector));

                if (diffuse==0.0) specular=0.0; 
                else specular=pow(specular,Material[MatIndex].shininess);

                scatteredLight += Lights[light].ambient+Lights[light].color*diffuse;
                reflectedLight += ReflectionLightColor*specular;
            }
        }
    }

    vec3 rgb = min(Color.rgb*scatteredLight+reflectedLight, vec3(1.0));

    fColor = texture(tex,vs_tex_coord) * vec4(rgb,Material[MatIndex].transparency); 
}