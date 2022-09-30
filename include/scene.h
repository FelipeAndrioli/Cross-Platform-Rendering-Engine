#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"

#include "../include/shader.h"
#include "../include/model.h"
#include "../include/camera.h"

#include "../src/scenes/pixel_rendering.h"
#include "../src/util/rendering_type.h"

class Scene {
    public:
        Scene(RenderingType rendering_type);
        ~Scene();
        void draw();
        void update(Camera *TheCamera);
        static void addModel(const char *raw_model_path, const char *model_id, 
            bool flip_texture);
        inline static std::vector<Model> models;
        std::vector<Shader> shaders;

        // these need to be removed
        Shader *SceneShader;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

    private:
        static std::string processPathInput(const char *input);
};
