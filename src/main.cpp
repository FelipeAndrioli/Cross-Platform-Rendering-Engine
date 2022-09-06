#include <iostream>

#include "state.h"

State state;

void init () {
    state.scene = new Scene();
    state.renderer = new Renderer(state.scene);
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
    state.renderer->update(state.scene, state.current_time); 
    state.renderer->draw(state.scene);
    state.ui->onUpdate(); 
    //std::cout << "Tick -> " << state.tick++ << std::endl;

    state.current_time = glfwGetTime();
    state.frames++;

    if (state.current_time - state.last_time >= 1.0f) {
        printf("%f ms/frame\n", 1000.0 / static_cast<double>(state.frames));
        printf("%f frame/s\n", state.frames / 1.0);
        state.frames = 0;
        state.last_time += 1.0;
    }
}

int main() {
    state.window = new Window(init, update);
    state.window->main_loop();

    return 0;
}
