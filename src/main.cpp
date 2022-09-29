#include <iostream>

#include "state.h"

State state;

void swapModes();

void init () {
    state.config_mode = false;
    state.rendering_type = SCENE;
    state.scene = new Scene(state.rendering_type);
    state.renderer = new Renderer();
    state.ui = new UI(state.window, swapModes, state.scene->addModel);

    state.ui->window_clear_color_r = &state.window->clear_color_r;
    state.ui->window_clear_color_g = &state.window->clear_color_g;
    state.ui->window_clear_color_b = &state.window->clear_color_b;

    state.last_time = glfwGetTime();
    state.frames = 0;
}

void tick() {
    std::cout << "Ticking..." << std::endl;
}

void update() {

    if (state.window->keyboard.keys[GLFW_KEY_0].pressed) {
        state.config_mode = true;
    }
    
    if (state.window->keyboard.keys[GLFW_KEY_9].pressed) {
        state.config_mode = false;
    }

    if (state.config_mode) {
        glfwSetInputMode(state.window->m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        state.window->mouse->first_mouse = true;
        state.window->keyboard.keys[GLFW_KEY_W].pressed = false;
        state.window->keyboard.keys[GLFW_KEY_A].pressed = false;
        state.window->keyboard.keys[GLFW_KEY_S].pressed = false;
        state.window->keyboard.keys[GLFW_KEY_D].pressed = false;
    } else {
        glfwSetInputMode(state.window->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    state.renderer->update(
        state.scene, 
        state.window->keyboard, 
        state.window->mouse, 
        state.delta_time, 
        state.current_time
    );

    state.scene->update(state.renderer->TheCamera);
    state.renderer->draw(state.scene);
    state.ui->onUpdate(); 
    //state.scene->draw();

    state.current_time = glfwGetTime();
    state.delta_time = state.current_time - state.last_time;
    state.frames++;
    state.last_time = state.current_time;


    /*
    if (state.current_time - state.last_time >= 1.0f) {
        printf("%f ms/frame\n", 1000.0 / static_cast<double>(state.frames));
        printf("%f frame/s\n", state.frames / 1.0);
        state.frames = 0;
        state.last_time += 1.0;
    }
    */
}

void destroy() {
    delete state.scene;
    delete state.renderer;
    delete state.ui;
    delete state.window;
}

void swapModes() {
    std::cout << "Work in progress" << std::endl;
}

int main() {
    state.window = new Window(init, update, destroy);
    state.window->main_loop();

    return 0;
}
