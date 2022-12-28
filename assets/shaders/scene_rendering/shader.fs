#version 440 core

struct Light {
    float ambient;
    float diffuse;
    float specular;
    float shininess;
};

struct Material {
    float shininess;
    sampler2D diffuse_texture;
    sampler2D specular_texture;
    sampler2D normal_texture;
};

struct LightSource {
    vec3 position;
    vec3 color;
};

#define NR_LIGHT_SOURCES 5

uniform Material material;
uniform Light light;
uniform LightSource lightSource[NR_LIGHT_SOURCES];
uniform vec3 viewPos; 

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main() {
    // ambient lighting
    vec3 ambient = light.ambient * vec3(texture(material.diffuse_texture, TexCoord));
 
    vec3 normal = normalize(Normal);
    vec3 diffuse = vec3(0.);
    vec3 specular = vec3(0.);

    for (int i = 0; i < NR_LIGHT_SOURCES; i++) {
        // diffuse lighting
        vec3 lightDir = normalize(lightSource[i].position - FragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        diffuse += light.diffuse * diff * vec3(texture(material.diffuse_texture, TexCoord)) * lightSource[i].color;

        // specular lighting
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectedDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectedDir), 0.0), max(light.shininess, 1.0));
        specular += light.specular * spec * vec3(texture(material.specular_texture, TexCoord)) * lightSource[i].color;
    }

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);    
} 
