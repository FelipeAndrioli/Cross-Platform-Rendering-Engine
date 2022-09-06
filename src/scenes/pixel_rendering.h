#pragma once

#include <vector>

const char* pixel_rendering_vertex = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/pixel_rendering.vs";
const char* pixel_rendering_fragment = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/pixel_rendering.fs";

std::vector<float> scene_vertices = {
    1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
};

std::vector<unsigned int> scene_indices = {
    0, 1, 2,
    0, 2, 3
};
