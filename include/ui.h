#pragma once

#include <iostream>

#include "../include/global.h"

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

class UI { 
    public:
        UI(GLFWwindow *window);
        ~UI();
        void onUpdate();
    private:
        ImGuiContext *imgui_context;
        void onCreate();
        void onDestroy();
};
