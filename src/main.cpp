#include <iostream>

#include "state.h"

State state;

void init() {
    state.config_mode = false;
    state.rendering_type = SCENE;
    state.scene = new Scene(state.rendering_type);
    state.renderer = new Renderer();
    state.ui = new UI();
   
    state.ui->p_current_frame_time = &state.current_frame_time;    
    state.ui->p_last_frame_time = &state.last_frame_time;    
    state.ui->p_delta_time = &state.delta_time; 
    state.ui->p_fps = &state.fps; 
    state.ui->p_ms = &state.ms; 

    state.frames = 0;
    state.fps = 0.0;
    state.ms = 0.0;

    state.ui->p_window = state.window;
    state.ui->p_renderer = state.renderer;
    state.ui->p_scene = state.scene;

    state.ui->onInit();
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
        state.delta_time
    );

    state.current_frame_time = glfwGetTime();
    state.renderer->draw(state.scene);
    state.delta_time = state.current_frame_time - state.last_frame_time; 
    state.frames++;

    if (state.delta_time >= 1.0 / 60.0) {
        state.fps = (1.0 / state.delta_time) * state.frames;
        state.ms = (state.delta_time / state.frames) * 1000;
        state.last_frame_time = state.current_frame_time;
        state.frames = 0;
    } 
    
    state.ui->onUpdate(); 
}

void destroy() {
    delete state.scene;
    delete state.renderer;
    delete state.ui;
    delete state.window;
}

int main() {
    state.window = new Window(init, update, destroy);
    state.window->main_loop();

    return 0;
}
