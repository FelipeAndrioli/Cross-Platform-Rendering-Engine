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
        unsigned int ticks;
        GLFWwindow *m_window;
        void window_create();
        void window_destroy();
        void processInput();
        static void framebuffer_size_callback(GLFWwindow *t_window, int width, int height);
    public:
        const char *window_name;

        Window();
        Window(const char *t_window_name, int t_window_width, int t_window_height);
        ~Window();
        void window_loop();
        void resize(int new_width, int new_height);
};
