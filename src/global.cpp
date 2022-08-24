#include "../include/global.h"

Global::Global() {
    std::cout << "Initializing global configuration..." << std::endl; 
}

void Global::resizeWindow(int new_width, int new_height) {
    m_window.resize(new_width, new_height); 
}
