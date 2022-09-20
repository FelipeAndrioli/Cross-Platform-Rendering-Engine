#include "../include/renderer.h"

Renderer::Renderer() {

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

void Renderer::update(Scene *CurrentScene, Keyboard keyboard, Mouse mouse,
    float delta_time, float time) {

    glm::vec3 res = glm::vec3(800, 600, 0);

    CurrentScene->SceneShader->setFloat("global.iTime", time);
    CurrentScene->SceneShader->setVec3("iResolution", res);

    if (mouse.on_screen == GLFW_TRUE)
        std::cout << "Mouse x -> " << mouse.x << " Mouse y -> " << mouse.y << std::endl;

    glPolygonMode(GL_FILL, GL_FRONT_AND_BACK);
    glEnable(GL_DEPTH_TEST);

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
 
    CurrentScene->draw();
    /*
    CurrentScene->SceneShader->use();
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, sizeof(CurrentScene->indices.size()), 
        GL_UNSIGNED_INT, 0);
    */
}
