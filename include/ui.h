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
        UI(Window *window, void(*swapModes)(), void(*resetSceneModels)(), 
            void(*addModel)(const char *model_path, std::string model_id, 
            bool flip_texture), void(*deleteModel)(std::string id));
        ~UI();
        void onUpdate();
        float *window_clear_color_r;
        float *window_clear_color_g;
        float *window_clear_color_b;

        bool flip_texture;

        double *p_current_frame_time;
        double *p_last_frame_time;
        double *p_delta_time;
        double *p_fps;
        double *p_ms;

        std::vector<Model*> *scene_models;

        Renderer *p_renderer;
    private:
        typedef void (*void_function)();
        typedef void (*void_one_param_function)(std::string id);
        typedef void (*void_two_param_function)(const char *param_one, 
            std::string param_two, bool param_bool);

        void_function m_swap;
        void_function m_resetScene;
        void_one_param_function m_deleteModel;
        void_two_param_function m_addModel;

        ImGuiContext *imgui_context;
        void onCreate();
        void onDestroy();

        static bool model_getter(void *data, int index, const char** output);
};
