#include "../include/scene.h"

Scene::Scene(RenderingType rendering_type) {

    if (rendering_type == PIXEL) {
        std::cout << "Rendering Pixels..." << std::endl;

        SceneShader = new Shader(PixelRendering::pixel_rendering_vertex, 
            PixelRendering::pixel_rendering_fragment, nullptr);

        vertices = PixelRendering::scene_vertices;
        indices = PixelRendering::scene_indices;
    }

    if (rendering_type == SCENE) {
        std::cout << "Rendering Scene..." << std::endl;
    }
}

Scene::~Scene() {
    std::cout << "Destroying Scene..." << std::endl;
}
