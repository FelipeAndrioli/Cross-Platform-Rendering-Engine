#pragma once

#include <iostream>
#include <vector>

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

#include "../include/window.h"

class UI { 
    public:
        UI(Window *window);
        ~UI();
        void onUpdate();
        float *r;
        float *g;
        float *b;
    private:
        ImGuiContext *imgui_context;
        void onCreate();
        void onDestroy();
};
