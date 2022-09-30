#pragma once

#include <iostream>
#include <vector>

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

#include "../include/window.h"

class UI { 
    public:
        UI(Window *window, void(*swapModes)(), void(*addModel)
            (const char *model_path, const char *model_id, bool flip_texture));
        ~UI();
        void onUpdate();
        float *window_clear_color_r;
        float *window_clear_color_g;
        float *window_clear_color_b;

        bool flip_texture;

    private:
        typedef void (*void_function)();
        typedef void (*void_two_param_function)(const char *param_one, 
            const char *param_two, bool param_bool);

        void_function m_swap;
        void_two_param_function m_addModel;

        ImGuiContext *imgui_context;
        void onCreate();
        void onDestroy();
};
