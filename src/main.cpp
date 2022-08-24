#include <iostream>

#include "../include/global.h"

Global global = Global();

int main() {
    Window m_window = Window("Application.exe", 800, 600);
    global.m_window = m_window;
    m_window.window_loop();
}
