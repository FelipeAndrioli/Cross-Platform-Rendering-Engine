#pragma once

#include <string>

#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/imgui_impl_glfw.h"
#include "../../libs/imgui/imgui_impl_opengl3.h"
#include "../../libs/glm/glm/glm.hpp"

class UI_Model {
    public:
        UI_Model();
        ~UI_Model();
        void onUpdate();
        std::string id;
        glm::vec3 *translation;
        glm::vec3 *scalation;
};
