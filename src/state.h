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

        const int TICKS_PER_SECOND = 30;
        const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
        const int MAX_FRAMESKIP = 10;
        // End timing

        bool config_mode;

        RenderingType rendering_type;
};
