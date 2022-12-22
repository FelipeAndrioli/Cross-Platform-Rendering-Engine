#version 440 core

struct Light {
    float ambient;
    float diffuse;
    float specular;
    vec3 position;
    vec3 color;
};

struct Material {
    float shininess;
    vec3 color;
};

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main() {
    vec3 ambient = light.ambient * material.color;

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.color;// + light.color;

    FragColor = vec4(ambient + diffuse, 1.0);
}
