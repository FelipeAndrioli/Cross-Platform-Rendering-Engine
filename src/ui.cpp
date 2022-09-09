#include "../include/ui.h"

UI::UI(Window *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->m_window, true);
    ImGui_ImplOpenGL3_Init("#version 440");
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

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::onDestroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
