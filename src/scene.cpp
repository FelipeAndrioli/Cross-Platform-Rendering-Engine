#include "../include/scene.h"

Scene::Scene() {

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

void Scene::attachShader() {
    for (int i = 0; i < models.size(); i++) {
        models[i]->attached_shader = p_shaders->at(0);
    }
}

void Scene::attachShader(std::string shader_id, std::string model_id) {
    Model *model = nullptr;
    Shader *shader = nullptr;

    for (int i = 0; i < models.size(); i++) {
        if (models[i]->model_id == model_id) {
            model = models[i]; 
            break;
        }
    }

    if (model == nullptr)
        return;

    for (int i = 0; i < p_shaders->size(); i++) {
        if (p_shaders->at(i)->readable_id == shader_id) {
            shader = p_shaders->at(i);
            break;
        }
    }

    if (shader == nullptr)
        return;

    model->attached_shader = shader;
    std::cout << "Shader -> " << shader->readable_id << " attached to the model -> " 
        << model->model_id << " successfully" << std::endl;
}

void Scene::setTextured(std::string model_id) {
    
}

void Scene::update(Settings *settings, Camera *TheCamera) {
    for (int i = 0; i < models.size(); i++) {
        models[i]->onUpdate(settings, TheCamera); 
    }
}

void Scene::addModel(const char *raw_model_path, std::string model_id,
    bool flip_texture) {
    std::string new_path = processPathInput(raw_model_path);
    const char *model_path = new_path.c_str();
    Model *new_model = new Model(model_path, model_id, flip_texture);
    new_model->attached_shader = p_shaders->at(0);
    models.push_back(new_model);
}

void Scene::addCustomModel() {
    Model *new_model = new Model();
    new_model->model_id = "Cube";
    new_model->attached_shader = p_shaders->at(0);
    models.push_back(new_model);
}

void Scene::resetSceneModels() {
    models.clear();
}

void Scene::deleteModel(std::string id) {
    for (int i = 0; i < models.size(); i++) {
        if (models[i]->model_id == id) {
            models.erase(models.begin() + i);
            break;
        }
    }
}

Scene::~Scene() {
    std::cout << "Destroying Scene..." << std::endl;
}
