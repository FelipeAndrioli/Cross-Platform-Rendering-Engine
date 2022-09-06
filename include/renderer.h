#pragma once

#include <iostream>

#include "../include/shader.h"

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"
#include "../libs/glm/glm/vec3.hpp"

class Renderer {
    public:
        Renderer();
        void draw();
        void update(float time);
    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        Shader *shader;
        const char* pixel_rendering_vertex = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/pixel_rendering.vs";
        const char* pixel_rendering_fragment = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/pixel_rendering.fs";
};
