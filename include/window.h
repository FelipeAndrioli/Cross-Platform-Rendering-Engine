#pragma once

#include <iostream>
#include <string>

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"

/* TODO
 *
 * - Fix framebuffer_size_callback function
 * - Add key processing
 * - Add tick processing
 *
 * */

class Window {
    private:
        int glfw_context_version_minor;
        int glfw_context_version_major;
        int opengl_profile;
        int window_width;
        int window_height;
        float clear_color_r; 
        float clear_color_g; 
        float clear_color_b; 
        const char *window_name;
        void window_create();
        void window_destroy();
        void processInput();
        static void framebuffer_size_callback(GLFWwindow *t_window, int width, int height);
    public:
        Window();
        Window(void(*update)());
        ~Window();
        void main_loop();
        void resize(int new_width, int new_height);
        GLFWwindow *m_window;
};
