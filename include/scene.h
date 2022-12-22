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
        static void resetSceneModels();
        static void addModel(const char *raw_model_path, std::string model_id, 
            bool flip_texture);
        void addCustomModel(std::string model_id);
        void addLightSource(std::string light_id);
        static void deleteModel(std::string id);
        static void deleteLightsource(std::string id);
        inline static std::vector<Model*> models;
        inline static std::vector<LightSource*> light_sources;
        inline static std::vector<Shader*> *p_shaders;

        void attachShader();
        void attachShader(std::string shader_id, std::string model_id);
    private:
        static std::string processPathInput(const char *input);
};
