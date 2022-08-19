#include "../include/gui.h"

GUI::GUI(GLFWwindow *window) {
    gui_window = window;
}

void GUI::Update() {
    onUpdate();
}

GUI::~GUI() {
    onDestroy();
}

void GUI::onCreate() {
    IMGUI_CHECKVERSION();
    gui_context = ImGui::CreateContext();
    ImGui::SetCurrentContext(gui_context);
    ImGuiIO &io = ImGui::GetIO(); 
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(gui_window, true);
}

void GUI::onUpdate() {
    ImGui::SetCurrentContext(gui_context);
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Configurations");
}

void GUI::onDestroy() {
    ImGui::SetCurrentContext(gui_context);
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
