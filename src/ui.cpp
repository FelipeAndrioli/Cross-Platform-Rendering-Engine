#include "../include/ui.h"

UI::UI(Window *window, void(*swapModes)(), void(*addModel)
    (const char *model_path)) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->m_window, true);
    ImGui_ImplOpenGL3_Init("#version 440");

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
    //static char v_shader_path[128] = "";
    //static char f_shader_path[128] = "";

    ImGui::InputText("Model path", t_model_path, IM_ARRAYSIZE(t_model_path));

    if (ImGui::Button("Add model")) {
        std::cout << "Loading model..." << std::endl;
        const char *model_path = t_model_path;
        m_addModel(model_path);
    }

    if (ImGui::Button("Swap modes")) {
        std::cout << "Swaping between modes..." << std::endl;
        m_swap();
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::onDestroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
