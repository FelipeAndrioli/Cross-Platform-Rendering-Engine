#include <iostream>

#include "state.h"

State state;

void init () {
    std::cout << "Initializing..." << std::endl;
    state.ui = new UI(state.window);

    state.ui->r = &state.window->clear_color_r;
    state.ui->g = &state.window->clear_color_g;
    state.ui->b = &state.window->clear_color_b;
}

void update() {
    state.ui->onUpdate(); 
    std::cout << "Tick -> " << state.tick++ << std::endl;
}

int main() {
    state.window = new Window(init, update);
    state.window->main_loop();

    return 0;
}
