#pragma once

#include <iostream>

#include "./window.h"
#include "./ui.h"

class Global {
    public:
        Global();
        Window m_window;
        UI m_UI;

        void resizeWindow(int new_width, int new_height);
};
