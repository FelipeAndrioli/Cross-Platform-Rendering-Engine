#include <iostream>

#include "../include/ui.h"
#include "../include/window.h"
#include "../include/renderer.h"

class State {
    public:
        Window *window;
        Renderer *renderer;
        UI *ui;
        double last_time;
        double current_time;
        int tick;
        int frames;
};
