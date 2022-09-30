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

        //const char *backpack_model_path = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/models/backpack/backpack.obj";

        //Shader *backpack_shader = new Shader(bp_v_shader, bp_f_shader, nullptr);
        //Model *backpack_model = new Model(backpack_model_path);

        //models.push_back(*backpack_model);
        //shaders.push_back(*backpack_shader);

        const char *v_shader = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/scene_rendering/backpack_shaders/shader.vs";
        const char *f_shader = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/scene_rendering/backpack_shaders/shader.fs";
        Shader *basic_shaders = new Shader(v_shader, f_shader, nullptr);

        shaders.push_back(*basic_shaders);
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
    for (int i = 0; i < shaders.size(); i++) {
        shaders[i].use();
        glm::mat4 projection = glm::perspective(TheCamera->Zoom, 
            (float)800/(float)600, 0.1f, 100.0f);
        glm::mat4 view = TheCamera->getViewMatrix();

        shaders[i].setMat4("projection", projection);
        shaders[i].setMat4("view", view);
      
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

        shaders[i].setMat4("model", model);
    }
}

void Scene::addModel(const char *raw_model_path, const char *model_id,
    bool flip_texture) {
    std::string new_path = processPathInput(raw_model_path);
    const char *model_path = new_path.c_str();
    Model *new_model = new Model(model_path, model_id, flip_texture);
    models.push_back(*new_model);
}

void Scene::draw() {
    for (int i = 0; i < models.size(); i++) {
        for (int j = 0; j < shaders.size(); j++) {
            models[i].Draw(shaders[j]);
        }
    }
}

Scene::~Scene() {
    std::cout << "Destroying Scene..." << std::endl;
}
