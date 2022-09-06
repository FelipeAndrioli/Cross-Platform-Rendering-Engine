#include "../include/scene.h"

Scene::Scene() {
    std::cout << "Initializing Scene..." << std::endl; 

    const char* pixel_rendering_vertex = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/pixel_rendering.vs";
    const char* pixel_rendering_fragment = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/pixel_rendering.fs";

    SceneShader = new Shader(pixel_rendering_vertex, pixel_rendering_fragment,
        nullptr);

    vertices = {
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };

    indices = {
        0, 1, 2,
        0, 2, 3
    };

    /*
    SceneShader = new Shader(PixelRendering::pixel_rendering_vertex, 
        PixelRendering::pixel_rendering_fragment, nullptr);

    *vertices = PixelRendering::vertices;
    *indices = PixelRendering::indices;
    */
}
