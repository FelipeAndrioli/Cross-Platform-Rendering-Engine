#include "../include/scene.h"

Scene::Scene(RenderingType rendering_type) {

    if (rendering_type == PIXEL) {
        std::cout << "Rendering Pixels..." << std::endl;

        SceneShader = new Shader(PixelRendering::pixel_rendering_vertex, 
            PixelRendering::pixel_rendering_fragment, nullptr);

        vertices = PixelRendering::scene_vertices;
        indices = PixelRendering::scene_indices;
    }

    if (rendering_type == SCENE) {
        std::cout << "Rendering Scene..." << std::endl;

        std::filesystem::path current_path = std::filesystem::current_path();

        std::string v_shader = current_path.parent_path().string();
        v_shader += "/src/shaders/scene_rendering/shader.vs";

        std::string f_shader = current_path.parent_path().string();
        f_shader += "/src/shaders/scene_rendering/shader.fs";

        SceneShader = new Shader(v_shader.c_str(), f_shader.c_str(), nullptr);
    }
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
        SceneShader->use();
        glm::mat4 projection = glm::perspective(TheCamera->Zoom, 
            (float)800/(float)600, 0.1f, 100.0f);
        glm::mat4 view = TheCamera->getViewMatrix();
     
        SceneShader->setMat4("projection", projection);
        SceneShader->setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);

        models[i]->model_transformations->scalation = glm::vec3(models[i]->scale_handler);
        model = glm::scale(model, models[i]->model_transformations->scalation);
        model = glm::translate(model, models[i]->model_transformations->translation);
        model = glm::rotate(model, models[i]->model_transformations->rotation.x, 
            glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, models[i]->model_transformations->rotation.y, 
            glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, models[i]->model_transformations->rotation.z, 
            glm::vec3(0.0f, 0.0f, 1.0f));

        SceneShader->setMat4("model", model);

        models[i]->Draw(*SceneShader);
    }
}

Scene::~Scene() {
    std::cout << "Destroying Scene..." << std::endl;
}
