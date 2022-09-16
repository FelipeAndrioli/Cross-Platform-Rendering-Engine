#pragma once

#include <iostream>
#include <vector>

#include "../include/shader.h"
#include "../include/scene.h"
#include "../include/camera.h"

#include "../src/util/camera_movement.h"
#include "../src/util/keyboard.h"

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"
#include "../libs/glm/glm/vec3.hpp"

class Renderer {
    public:
        Renderer();
        Renderer(Scene *CurrentScene);
        ~Renderer();
        void draw(Scene *CurrentScene);
        void update(Scene *CurrentScene, Keyboard keyboard, float delta_time, 
            float time);
        Camera *TheCamera;
    private:
        Scene *TheScene;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
};
