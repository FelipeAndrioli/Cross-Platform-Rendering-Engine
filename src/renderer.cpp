#include "../include/renderer.h"

Renderer::Renderer() {

    std::cout << "Initializing Renderer" << std::endl;
    TheCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    wireframe = false;
    depth_test = true;

    updateWireframe();
    enableFeature(GL_DEPTH_TEST);
}

Renderer::~Renderer() {
    std::cout << "Destroying Renderer..." << std::endl;
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

void Renderer::update(Scene *CurrentScene, Keyboard keyboard, Mouse *mouse,
    float delta_time, float time) {

    glm::vec3 res = glm::vec3(800, 600, 0);
    CurrentScene->SceneShader->setFloat("global.iTime", time);
    CurrentScene->SceneShader->setVec3("iResolution", res);
   
    updateCamera(keyboard, mouse, delta_time, time);
}

void Renderer::draw(Scene *CurrentScene) {
    CurrentScene->draw(TheCamera);
}
