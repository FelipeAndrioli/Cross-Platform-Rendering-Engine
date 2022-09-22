#include <iostream>

#include "../include/ui.h"
#include "../include/window.h"
#include "../include/renderer.h"
#include "../include/scene.h"

#include "./util/rendering_type.h"

class State {
    public:
        Window *window;
        Renderer *renderer;
        UI *ui;
        Scene *scene;

        float last_time;
        float current_time;
        float delta_time;

        int tick;
        int frames;

        bool config_mode;

        RenderingType rendering_type;
};
