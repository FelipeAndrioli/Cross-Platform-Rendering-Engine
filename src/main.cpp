#include <iostream>

#include "state.h"

State state;

void init () {
    state.renderer = new Renderer();
    state.ui = new UI(state.window);

    state.ui->window_clear_color_r = &state.window->clear_color_r;
    state.ui->window_clear_color_g = &state.window->clear_color_g;
    state.ui->window_clear_color_b = &state.window->clear_color_b;
    
    state.last_time = glfwGetTime();
    state.frames = 0;
}

void update() {
    state.renderer->update(state.current_time); 
    state.ui->onUpdate(); 
    //std::cout << "Tick -> " << state.tick++ << std::endl;

    state.current_time = glfwGetTime();
    state.frames++;

    if (state.current_time - state.last_time >= 1.0f) {
        printf("%f ms/frame\n", 1000.0 / static_cast<double>(state.frames));
        state.frames = 0;
        state.last_time += 1.0;
    }
}

void tick() {


}

int main() {
    state.window = new Window(init, update);
    state.window->main_loop();

    return 0;
}
