#include "../include/renderer.h"

Renderer::Renderer() {

    std::cout << "Initializing Renderer" << std::endl;
    TheCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    clear_color = new Color();
    clear_color->r = 0.5f; 
    clear_color->g = 0.5f; 
    clear_color->b = 0.5f; 
    clear_color->a = 1.0f; 

    wireframe = false;
    depth_test = true;

    updateWireframe();
    enableFeature(GL_DEPTH_TEST);
    
    initializeShaders();
}

Renderer::~Renderer() {
    std::cout << "Destroying Renderer..." << std::endl;
    delete TheCamera;
}

void Renderer::enableFeature(GLenum feature) {
    glEnable(feature);
}

void Renderer::disableFeature(GLenum feature) {
    glDisable(feature);
}

void Renderer::updateWireframe() {
    if (wireframe) { 
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Renderer::updateCamera(Keyboard keyboard, Mouse *mouse, float delta_time,
    float time) {
    
    if (mouse->on_screen == GLFW_TRUE) {
        float new_x = static_cast<float>(mouse->x);
        float new_y = static_cast<float>(mouse->y);

        if (mouse->first_mouse) {
            mouse->last_x = new_x; 
            mouse->last_y = new_y; 
            mouse->first_mouse = false;
        }

        float x_offset = mouse->x - mouse->last_x;
        float y_offset = mouse->last_y - mouse->y;

        mouse->last_x = mouse->x;
        mouse->last_y = mouse->y;

        TheCamera->processMouseMovement(x_offset, y_offset);        
    } 

    if (keyboard.keys[GLFW_KEY_W].pressed) 
        TheCamera->processKeyboard(FORWARD, delta_time);
    
    if (keyboard.keys[GLFW_KEY_S].pressed) 
        TheCamera->processKeyboard(BACKWARD, delta_time);
    
    if (keyboard.keys[GLFW_KEY_A].pressed) 
        TheCamera->processKeyboard(LEFT, delta_time);
    
    if (keyboard.keys[GLFW_KEY_D].pressed)  
        TheCamera->processKeyboard(RIGHT, delta_time);
}

void Renderer::update(Scene *CurrentScene, Settings *settings, Keyboard keyboard, 
    Mouse *mouse, float delta_time, float time) {
    glm::vec3 res = glm::vec3(settings->resolution.x, settings->resolution.y, 0);
    // TODO need to set it in the correct place
    //shaders.at(0)->setFloat("global.iTime", time);
    //shaders.at(0)->setVec3("iResolution", res);

    glClearColor(clear_color->r, clear_color->g, clear_color->b, 
        clear_color->a);
    updateCamera(keyboard, mouse, delta_time, time);

    CurrentScene->update(settings, TheCamera);
}

void Renderer::draw(Scene *CurrentScene) {
    //CurrentScene->draw(TheCamera);
    prepare(CurrentScene, TheCamera);
}

void Renderer::render(Shader *shader, unsigned int VAO, unsigned int indices_size) {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Renderer::prepare(Scene *CurrentScene, Camera *TheCamera) {
    for (int i = 0; i < CurrentScene->models.size(); i++) {
        Model *model = CurrentScene->models[i];

        for (unsigned int j = 0; j < model->meshes.size(); j++) {
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr = 1;
            unsigned int heightNr = 1;

            for (unsigned int k = 0; k < model->meshes[j].textures.size(); k++) {
                glActiveTexture(GL_TEXTURE0 + k);

                std::string number;
                std::string name = model->meshes[j].textures[k].type;

                if (name == "texture_diffuse") {
                    number = std::to_string(diffuseNr++);
                } else if (name == "texture_specular") {
                    number = std::to_string(specularNr++);
                } else if (name == "texture_normal") {
                    number = std::to_string(normalNr++);
                } else if (name == "texture_height") {
                    number = std::to_string(heightNr++);
                }

                model->attached_shader->setInt(("material." + name + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, model->meshes[j].textures[k].id);
            }
            model->setUniforms(model->attached_shader);
            render(model->attached_shader, model->meshes[j].VAO, model->meshes[j].indices.size());
        }
    }
}

void Renderer::reloadShaders(Scene *CurrentScene) {
    std::string existing_shader_id;
    std::string v_shader;
    std::string f_shader;
    //std::string g_shader;

    for (int i = 0; i < shaders.size(); i++) {
        existing_shader_id = shaders[i]->readable_id;
        v_shader = shaders[i]->vertex_shader_path;
        f_shader = shaders[i]->fragment_shader_path;
        //g_shader = shaders[i]->geometry_shader_path;

        shaders.erase(shaders.begin() + i);
    
        Shader *shader = new Shader(existing_shader_id.c_str(), v_shader.c_str(), 
            f_shader.c_str(), nullptr);
        shaders.push_back(shader);
    }

    CurrentScene->attachShader();
}

void Renderer::reloadShader(std::string shader_id, Scene *CurrentScene) {
    std::string existing_shader_id;
    std::string v_shader;
    std::string f_shader;
    //std::string g_shader;

    for (int i = 0; i < shaders.size(); i++) {
        if (shaders[i]->readable_id == shader_id) {
            existing_shader_id = shaders[i]->readable_id;
            v_shader = shaders[i]->vertex_shader_path;
            f_shader = shaders[i]->fragment_shader_path;
            //g_shader = shaders[i]->geometry_shader_path;

            shaders.erase(shaders.begin() + i);
            break;
        }
    }

    Shader *shader = new Shader(existing_shader_id.c_str(), v_shader.c_str(), 
        f_shader.c_str(), nullptr);
    shaders.push_back(shader);
    CurrentScene->attachShader();
}

void Renderer::initializeShaders() {
    std::filesystem::path current_path = std::filesystem::current_path();
    
    shaders_directory_path = current_path.parent_path().string();
    shaders_directory_path += "/src/shaders/scene_rendering/";

    std::string v_shader = shaders_directory_path + "shader.vs";
    std::string f_shader = shaders_directory_path + "shader.fs";

    Shader *shader = new Shader("Basic Shader", v_shader.c_str(), f_shader.c_str(), nullptr);
    shaders.push_back(shader);

}

