#pragma once

#include "../../libs/glfw/include/GLFW/glfw3.h"

typedef struct {
    bool pressed;
} Key;

typedef struct {
    Key keys[GLFW_KEY_LAST];
} Keyboard;
