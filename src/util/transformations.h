#pragma once

#include "../../libs/glm/glm/glm.hpp"

typedef struct {
    glm::vec3 translation;
    glm::vec3 scalation;
    glm::vec3 rotation;
} Transformations;

typedef struct {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
} TransformationsMatrices;
