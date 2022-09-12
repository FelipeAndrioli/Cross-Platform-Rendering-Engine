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

        const char *backpack_model_path = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/models/backpack/backpack.obj";
        const char *bp_v_shader = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/scene_rendering/backpack_shaders/shader.vs";
        const char *bp_f_shader = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/scene_rendering/backpack_shaders/shader.fs";

        Shader *backpack_shader = new Shader(bp_v_shader, bp_f_shader, nullptr);
        Model *backpack_model = new Model(backpack_model_path);

        models.push_back(*backpack_model);
        shaders.push_back(*backpack_shader);

        glm::mat4 projection = glm::perspective(90.0f, (float)800/(float)600, 0.1f, 100.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        backpack_shader->setMat4("projection", projection);
        backpack_shader->setMat4("view", view);
        backpack_shader->setMat4("model", model);
    }
}

void Scene::draw() {
    for (int i = 0; i < 1; i++) {
        backpack_shader->setMat4("projection", projection);
        backpack_shader->setMat4("view", view);
        backpack_shader->setMat4("model", model);
        models[i].Draw(shaders[i]);
    }
}

Scene::~Scene() {
    std::cout << "Destroying Scene..." << std::endl;
}
