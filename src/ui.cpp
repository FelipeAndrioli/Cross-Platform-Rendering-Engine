#include "../include/ui.h"

UI::UI(Window *window, void(*swapModes)(), void(*addModel)
    (const char *model_path, const char *model_id, bool flip_texture)) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->m_window, true);
    ImGui_ImplOpenGL3_Init("#version 440");

    flip_texture = true;

    m_swap = swapModes;
    m_addModel = addModel;
}

UI::~UI() {
    onDestroy();
    std::cout << "Destroying UI..." << std::endl;
}

void UI::onUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Configurations");

    if (ImGui::Button("Test")) {
        std::cout << "Hello there!" << std::endl;  
    }

    ImGui::SliderFloat("Clear Color R", window_clear_color_r, 0.0f, 1.0f);
    ImGui::SliderFloat("Clear Color G", window_clear_color_g, 0.0f, 1.0f);
    ImGui::SliderFloat("Clear Color B", window_clear_color_b, 0.0f, 1.0f);

    static char t_model_path[128] = "";
    static char t_model_id[128] = "";
    //static char v_shader_path[128] = "";
    //static char f_shader_path[128] = "";

    ImGui::InputText("Model id", t_model_id, IM_ARRAYSIZE(t_model_id));
    ImGui::InputText("Model path", t_model_path, IM_ARRAYSIZE(t_model_path));
    ImGui::Checkbox("STBI Flip Vertically", &flip_texture);
    
    if (ImGui::Button("Add model")) {
        std::cout << "Loading model..." << std::endl;
        const char *model_path = t_model_path;
        const char *model_id = t_model_id;
        m_addModel(model_path, model_id, flip_texture);
    }
    
    if (ImGui::Button("Swap modes")) {
        std::cout << "Swaping between modes..." << std::endl;
        m_swap();
    }

    // each model

    for (int i = 0; i < scene_models.size(); i++) {
        ImGui::TextUnformatted(scene_models[i].model_id); 
    }

    // end each model

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::onDestroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
