#include "./ui_model.h"

UI_Model::UI_Model() {

}

UI_Model::~UI_Model() {

}

void UI_Model::onUpdate() {
    ImGui::Begin(id.c_str());
    ImGui::SliderFloat("Translation x", &translation->x, -50.0f, 50.0f);
    ImGui::SliderFloat("Translation y", &translation->y, -50.0f, 50.0f);
    ImGui::SliderFloat("Translation z", &translation->z, -50.0f, 50.0f);
    ImGui::End();
}
