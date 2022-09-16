#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"

#include "../include/shader.h"
#include "../include/model.h"
#include "../include/camera.h"

#include "../src/scenes/pixel_rendering.h"

enum RenderingType {
    PIXEL,
    SCENE
};

class Scene {
    public:
        Scene(RenderingType rendering_type);
        ~Scene();
        void draw();
        void update(Camera *TheCamera);
        std::vector<Model> models;
        std::vector<Shader> shaders;

        // these need to be removed
        Shader *SceneShader;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
};
