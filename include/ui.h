#pragma once

#include <iostream>
#include <vector>

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"

#include "../include/window.h"
#include "../include/model.h"
#include "../include/renderer.h"

#include "../src/ui/ui_model.h"

class UI { 
    public:
        UI();
        ~UI();
        void onInit();
        void onUpdate();

        bool flip_texture;

        double *p_current_frame_time;
        double *p_last_frame_time;
        double *p_delta_time;
        double *p_fps;
        double *p_ms;

        Renderer *p_renderer;
        Scene *p_scene;
        Window *p_window;
    private:
        ImGuiContext *imgui_context;
        void onDestroy();
};
