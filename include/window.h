#pragma once

#include <iostream>
#include <string>

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"

#include "../src/util/settings.h"
#include "../src/util/keyboard.h"
#include "../src/util/mouse.h"

/* TODO
 *
 * - Fix framebuffer_size_callback function
 *
 * */

class Window {
    private:
        typedef void (*void_function)();

        int glfw_context_version_minor;
        int glfw_context_version_major;
        int opengl_profile;
        const char *window_name;
        void window_create();
        void initialize_mouse();
        void initialize_keyboard();

        void_function m_init;
        void_function m_update;
        void_function m_destroy;
        
        static void framebuffer_size_callback(GLFWwindow *t_window, int width, 
            int height);
        static void key_callback(GLFWwindow *t_window, int key, int scancode, 
            int action, int mods);
        static void cursor_position_callback(GLFWwindow *t_window, double x_pos, 
            double y_pos);
        static void cursor_enter_callback(GLFWwindow *t_window, int entered);
    public:
        Window();
        Window(void(*init)(), void(*update)(), void(*destroy)());
        ~Window();
        void main_loop();
        void resize(int new_width, int new_height);
        GLFWwindow *m_window;
        float clear_color_r; 
        float clear_color_g; 
        float clear_color_b;

        inline static Keyboard keyboard;
        inline static Mouse *mouse;
        inline static Settings *p_settings;
};
