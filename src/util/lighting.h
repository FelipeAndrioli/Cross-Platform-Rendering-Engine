#pragma once

#include <iostream>

#include "../../libs/glm/glm/glm.hpp"

typedef struct {
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} BasicLight;

typedef struct {
    std::string id;
    bool enable;
    glm::vec3 position;
    glm::vec3 color;

} LightSource;
