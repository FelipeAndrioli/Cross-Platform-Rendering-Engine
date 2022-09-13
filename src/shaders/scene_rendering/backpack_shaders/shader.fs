#version 440 core

struct Material {
    float shininess;
    sampler2D diffuse_texture;
    sampler2D specular_texture;
    sampler2D normal_texture;
};

uniform Material material;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main() {
    vec3 ambient = 1.0 * vec3(texture(material.diffuse_texture, TexCoord));

    FragColor = vec4(ambient, 1.0);    
} 
