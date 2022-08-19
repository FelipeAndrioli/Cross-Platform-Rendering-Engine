#pragma once

#include <iostream>
#include <string>

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

#include "../libs/glfw/include/GLFW/glfw3.h"

class GUI {
    public:
        GUI(GLFWwindow *window);
        ~GUI();
        void Update();
    private:
        void onCreate();
        void onUpdate();
        void onDestroy();
        GLFWwindow *gui_window;
        ImGuiContext *gui_context;
};
