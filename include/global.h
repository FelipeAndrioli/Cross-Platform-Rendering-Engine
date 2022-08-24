#pragma once

#include <iostream>

#include "./window.h"

class Global {
    public:
        Global();
        Window m_window;

        void resizeWindow(int new_width, int new_height);
};
