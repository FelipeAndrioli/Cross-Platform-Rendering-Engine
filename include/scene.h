#pragma once

#include <iostream>
#include <vector>

#include "../include/shader.h"
#include "../include/model.h"
#include "../src/scenes/pixel_rendering.h"

enum RenderingType {
    PIXEL,
    SCENE
};

class Scene {
    public:
        Scene(RenderingType rendering_type);
        ~Scene();
        std::vector<Model> models;

        // these need to be removed
        Shader *SceneShader;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
};
