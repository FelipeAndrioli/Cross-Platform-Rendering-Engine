#pragma once

#include "../../libs/glm/glm/glm.hpp"

/*
    - In the future if necessary would be good to turn this into a class 
*/

typedef struct {
    const char *window_title;
    glm::vec2 resolution; 
} Settings;
