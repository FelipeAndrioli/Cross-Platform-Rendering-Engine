#pragma once

#include <iostream>
#include <vector>

#include "../include/shader.h"
#include "../include/scene.h"
#include "../include/camera.h"

#include "../src/util/camera_movement.h"
#include "../src/util/keyboard.h"
#include "../src/util/mouse.h"

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"
#include "../libs/glm/glm/vec3.hpp"

class Renderer {
    public:
        Renderer();
        ~Renderer();
        void enableFeature(GLenum feature);
        void disableFeature(GLenum feature);
        void updateWireframe();
        void updateCamera(Keyboard keyboard, Mouse *mouse, float delta_time,
            float time);
        void draw(Scene *CurrentScene);
        void render(Shader *shader, unsigned int VAO, unsigned int indices_size);
        void update(Scene *CurrentScene, Keyboard keyboard, Mouse *mouse, 
            float delta_time, float time);
        void prepare(Scene *CurrentScene, Camera *TheCamera);
        Camera *TheCamera;

        bool wireframe;
        bool depth_test;
    private:
        Scene *TheScene;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
};
