#version 440 core

struct Light {
    float ambient;
    float diffuse;
    float specular;
};

struct Material {
    float shininess;
    vec3 color;
}

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main() {
    vec3 ambient = light.ambient * material.color;

    FragColor = vec4(ambient, 1.0);
}
