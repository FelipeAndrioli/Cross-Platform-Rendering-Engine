#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <unordered_map>

#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"

#include "../include/shader.h"
#include "../include/model.h"
#include "../include/camera.h"

#include "../src/scenes/pixel_rendering.h"
#include "../src/util/settings.h"

class Scene {
    public:
        Scene();
        ~Scene();
        void update(Settings *settings, Camera *TheCamera);
        void reloadShaders();
        static void resetSceneModels();
        static void addModel(const char *raw_model_path, std::string model_id, 
            bool flip_texture);
        static void deleteModel(std::string id);
        inline static std::vector<Model*> models;
        inline static std::vector<Shader*> shaders;

        Shader *SceneShader;
        std::string shader_path;
    private:
        static std::string processPathInput(const char *input);
};
