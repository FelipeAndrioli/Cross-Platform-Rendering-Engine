#include "../include/ui.h"

UI::UI() {

}

UI::~UI() {
    onDestroy();
    std::cout << "Destroying UI..." << std::endl;
}

void UI::onInit() {
    std::cout << "Initializing UI" << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(p_window->m_window, true);
    ImGui_ImplOpenGL3_Init("#version 440");

    flip_texture = true;
}

void UI::onUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Configurations");

    std::string handler = std::to_string(*p_current_frame_time) + " current frame time";
    ImGui::TextUnformatted(handler.c_str());
    handler = std::to_string(*p_last_frame_time) + " last frame time";
    ImGui::TextUnformatted(handler.c_str());
    handler = std::to_string(*p_delta_time) + " delta time";
    ImGui::TextUnformatted(handler.c_str());

    handler = std::to_string(*p_fps) + " fps";
    ImGui::TextUnformatted(handler.c_str());
    ImGui::SameLine();
    handler = std::to_string(*p_ms) + " ms";
    ImGui::TextUnformatted(handler.c_str());

    if (ImGui::Button("Debug")) {
        std::cout << "Objects amount -> " << p_scene->models.size() << std::endl;
    }

    ImGui::SliderFloat("Clear Color R", &p_window->clear_color_r, 0.0f, 1.0f);
    ImGui::SliderFloat("Clear Color G", &p_window->clear_color_g, 0.0f, 1.0f);
    ImGui::SliderFloat("Clear Color B", &p_window->clear_color_b, 0.0f, 1.0f);

    static char t_model_path[128] = "";
    static char t_model_id[128] = "";

    ImGui::InputText("Model id", t_model_id, IM_ARRAYSIZE(t_model_id));
    ImGui::InputText("Model path", t_model_path, IM_ARRAYSIZE(t_model_path));
    ImGui::Checkbox("STBI Flip Vertically", &flip_texture);
    
    if (ImGui::Button("Add model")) {
        /* TODO
         *
         * - Add validation when pressed with empty values
         *
         * */
        std::cout << "Loading model..." << std::endl;
        const char *model_path = t_model_path;
        const char *model_id = t_model_id;
        p_scene->addModel(model_path, model_id, flip_texture);
    }

    if (ImGui::Button("Reset Scene Models")) {
        p_scene->resetSceneModels();
    } 

    if (ImGui::Button("Update Shaders")) {
        p_scene->updateShaders();
    }

    if (ImGui::TreeNode("Renderer")) {
        if (ImGui::Checkbox("Wireframe", &p_renderer->wireframe)) {
            p_renderer->updateWireframe();
        }
        
        if (ImGui::Checkbox("Depth Test", &p_renderer->depth_test)) {
            if (p_renderer->depth_test) {
                p_renderer->enableFeature(GL_DEPTH_TEST);
            } else {
                p_renderer->disableFeature(GL_DEPTH_TEST);
            }
        }
        ImGui::TreePop();
    }

    // each model
    for (int i = 0; i < p_scene->models.size(); i++) {
        Model *current_model = p_scene->models.at(i);
        
        ImGui::Begin(current_model->model_id.c_str());

        if (ImGui::TreeNode("Transformations")) {
            std::string t_label_x = "Translation x " + current_model->model_id;
            std::string t_label_y = "Translation y " + current_model->model_id;
            std::string t_label_z = "Translation z " + current_model->model_id;
            
            std::string s_label = "Scalation " + current_model->model_id;

            std::string r_label_x = "Rotation x " + current_model->model_id;
            std::string r_label_y = "Rotation y " + current_model->model_id;
            std::string r_label_z = "Rotation z " + current_model->model_id;
          
            ImGui::SliderFloat(t_label_x.c_str(), 
                &current_model->model_transformations->translation.x, -50.0f, 50.0f);
            ImGui::SliderFloat(t_label_y.c_str(), 
                &current_model->model_transformations->translation.y, -50.0f, 50.0f);
            ImGui::SliderFloat(t_label_z.c_str(), 
                &current_model->model_transformations->translation.z, -50.0f, 50.0f);
            ImGui::SliderFloat(s_label.c_str(), &current_model->scale_handler, 
                0.0f, 3.0f);
            ImGui::SliderFloat(r_label_x.c_str(), 
                &current_model->model_transformations->rotation.x, -10.0f, 10.0f);
            ImGui::SliderFloat(r_label_y.c_str(), 
                &current_model->model_transformations->rotation.y, -10.0f, 10.0f);
            ImGui::SliderFloat(r_label_z.c_str(), 
                &current_model->model_transformations->rotation.z, -10.0f, 10.0f);
        
            ImGui::TreePop();
        }

        if (ImGui::Button("Delete model")) {
            p_scene->deleteModel(current_model->model_id);
        }
        ImGui::End();
    }
    // each model end
    
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::onDestroy() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
