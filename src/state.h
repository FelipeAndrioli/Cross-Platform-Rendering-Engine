#include <iostream>

#include "../include/ui.h"
#include "../include/window.h"
#include "../include/renderer.h"
#include "../include/scene.h"

class State {
    public:
        Window *window;
        Renderer *renderer;
        UI *ui;
        Scene *scene;
        double last_time;
        double current_time;
        int tick;
        int frames;
};
