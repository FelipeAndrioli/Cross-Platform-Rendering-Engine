#pragma once

typedef struct {
    double x;
    double y;
    double z;
    double last_x;
    double last_y;
    int on_screen;
    bool first_mouse;
} Mouse;
