#include "../include/renderer.h"

Renderer::Renderer() {

    std::cout << "Initializing Renderer" << std::endl;
    TheCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

Renderer::Renderer(Scene *CurrentScene) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, CurrentScene->vertices.size() * 
        sizeof(float), &CurrentScene->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, CurrentScene->indices.size() * 
        sizeof(unsigned int), &CurrentScene->indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Renderer::~Renderer() {
    std::cout << "Destroying Renderer..." << std::endl;
}

void Renderer::update(Scene *CurrentScene, Keyboard keyboard, Mouse *mouse,
    float delta_time, float time) {

    glm::vec3 res = glm::vec3(800, 600, 0);

    CurrentScene->SceneShader->setFloat("global.iTime", time);
    CurrentScene->SceneShader->setVec3("iResolution", res);

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

void Renderer::draw(Scene *CurrentScene) {
    CurrentScene->draw(TheCamera);
}
