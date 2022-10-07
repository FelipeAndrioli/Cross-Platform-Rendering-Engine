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

        // Start timing
        double current_frame_time;
        double last_frame_time;
        double delta_time;
        double fps;
        double ms;
        int frames;
        // End timing

        bool config_mode;

        RenderingType rendering_type;
};
