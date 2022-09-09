#pragma once

#include <iostream>
#include <vector>

#include "../include/shader.h"
#include "../include/scene.h"

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"
#include "../libs/glm/glm/vec3.hpp"

class Renderer {
    public:
        Renderer(Scene *CurrentScene);
        ~Renderer();
        void draw(Scene *CurrentScene);
        void update(Scene *CurrentScene, float time);
    private:
        Scene *TheScene;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
};
