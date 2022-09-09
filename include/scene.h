#pragma once

#include <iostream>
#include <vector>

#include "../include/shader.h"
#include "../src/scenes/pixel_rendering.h"

class Scene {
    public:
        Scene();
        ~Scene();
        Shader *SceneShader;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
};
