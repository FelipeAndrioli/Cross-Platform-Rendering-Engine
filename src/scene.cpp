#include "../include/scene.h"

Scene::Scene() {
    std::cout << "Rendering Scene..." << std::endl;

    std::filesystem::path current_path = std::filesystem::current_path();
    
    shader_path = current_path.parent_path().string();
    shader_path += "/src/shaders/scene_rendering/";

    std::string v_shader = shader_path + "shader.vs";
    std::string f_shader = shader_path + "shader.fs";

    SceneShader = new Shader(v_shader.c_str(), f_shader.c_str(), nullptr);
}

std::string Scene::processPathInput(const char *input) {
    std::string s = "";
    int i = 0;

    while (input[i] != '\0') {
        s += input[i];

        if (s[i] == '\\') { 
            s[i] = '/';
        }
        
        i++;
    }
    
    return s;
}

void Scene::update(Settings *settings, Camera *TheCamera) {
    for (int i = 0; i < models.size(); i++) {
        models[i]->onUpdate(settings, SceneShader, TheCamera); 
    }
}

void Scene::reloadShaders() {
    std::cout << "Updating shaders" << std::endl;

    delete SceneShader;
    
    std::string v_shader = shader_path + "shader.vs";
    std::string f_shader = shader_path + "shader.fs";

    SceneShader = new Shader(v_shader.c_str(), f_shader.c_str(), nullptr);
}

void Scene::addModel(const char *raw_model_path, std::string model_id,
    bool flip_texture) {
    std::string new_path = processPathInput(raw_model_path);
    const char *model_path = new_path.c_str();
    Model *new_model = new Model(model_path, model_id, flip_texture);
    models.push_back(new_model);
}

void Scene::addCustomModel() {
    Model *new_model = new Model();
    new_model->model_id = "Cube";
    models.push_back(new_model);
}

void Scene::resetSceneModels() {
    models.clear();
    shaders.clear();
}

void Scene::deleteModel(std::string id) {
    for (int i = 0; i < models.size(); i++) {
        if (models[i]->model_id == id) {
            models.erase(models.begin() + i);
        }
    }
}

Scene::~Scene() {
    std::cout << "Destroying Scene..." << std::endl;
}
