#include <iostream>

#include "state.h"

State state;

void update() {
    state.tick++;
    std::cout << "Tick -> " << state.tick << std::endl;
}

int main() {
    Window m_window = Window(update);
    state.window = &m_window;
    state.window->main_loop();
}
