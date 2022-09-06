#pragma once

#include <iostream>
#include <vector>

#include "../include/shader.h"

class Scene {
    public:
        Scene();
        Shader *SceneShader;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
};
