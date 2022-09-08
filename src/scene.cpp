#include "../include/scene.h"

Scene::Scene() {
    SceneShader = new Shader(PixelRendering::pixel_rendering_vertex, 
        PixelRendering::pixel_rendering_fragment, nullptr);

    vertices = PixelRendering::scene_vertices;
    indices = PixelRendering::scene_indices;
}
