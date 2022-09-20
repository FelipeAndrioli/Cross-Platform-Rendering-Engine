#include <iostream>

#include "state.h"

State state;

void init () {
    state.scene = new Scene(SCENE);
    //state.renderer = new Renderer(state.scene);
    state.renderer = new Renderer();
    state.ui = new UI(state.window);

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
    state.renderer->update(state.scene, state.window->keyboard, state.window->mouse,
        state.delta_time, state.current_time); 
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

int main() {
    state.window = new Window(init, update, destroy);
    state.window->main_loop();

    return 0;
}
