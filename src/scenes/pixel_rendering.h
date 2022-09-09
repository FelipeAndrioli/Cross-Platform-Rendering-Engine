#pragma once

#include <iostream>
#include <fstream>
#include <vector>

namespace PixelRendering {

    static const char* pixel_rendering_vertex = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/pixel_rendering_shaders/pixel_rendering.vs";
    static const char* pixel_rendering_fragment = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/pixel_rendering_shaders/pixel_rendering.fs";

    //static const char* pixel_rendering_vertex = "../shaders/pixel_rendering.vs";
    //static const char* pixel_rendering_fragment = "../shaders/pixel_rendering.fs";

    static std::vector<float> scene_vertices = {
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };

    static std::vector<unsigned int> scene_indices = {
        0, 1, 2,
        0, 2, 3
    };
}
