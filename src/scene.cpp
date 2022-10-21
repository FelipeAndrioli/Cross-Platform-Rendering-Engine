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

void Scene::update(Camera *TheCamera) {
    for (int i = 0; i < models.size(); i++) {
        //for (int j = 0; j < shaders.size(); j++) {
            //shaders[j]->use();
            SceneShader->use();
            glm::mat4 projection = glm::perspective(TheCamera->Zoom, 
                (float)800/(float)600, 0.1f, 100.0f);
            glm::mat4 view = TheCamera->getViewMatrix();

            //shaders[j]->setMat4("projection", projection);
            //shaders[j]->setMat4("view", view);
         
            SceneShader->setMat4("projection", projection);
            SceneShader->setMat4("view", view);

            glm::mat4 model = glm::mat4(1.0f);

            //model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
            //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

            models[i]->model_transformations->scalation = glm::vec3(models[i]->scale_handler);
            model = glm::scale(model, models[i]->model_transformations->scalation);
            model = glm::translate(model, models[i]->model_transformations->translation);
   
            std::cout << models[i]->model_id;
            std::cout << " " << models[i]->model_transformations->translation.x;
            std::cout << " " << models[i]->model_transformations->translation.y;
            std::cout << " " << models[i]->model_transformations->translation.z << std::endl;

            //shaders[j]->setMat4("model", model);
            SceneShader->setMat4("model", model);
        //}
    }
}

void Scene::updateShaders() {
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

void Scene::draw(Camera *TheCamera) {
    for (int i = 0; i < models.size(); i++) {
        models[i]->Draw(*SceneShader, TheCamera);
    }
}

Scene::~Scene() {
    std::cout << "Destroying Scene..." << std::endl;
}
