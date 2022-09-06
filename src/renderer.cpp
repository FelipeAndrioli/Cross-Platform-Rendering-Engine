#include "../include/renderer.h"

Renderer::Renderer() {
    std::cout << "Initializing renderer..." << std::endl;
    
    float screen[] = {
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,

        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f
    };

    shader = new Shader(pixel_rendering_vertex, pixel_rendering_fragment, nullptr);
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(screen), screen, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Renderer::update(float time) {

    glm::vec3 res = glm::vec3(800, 600, 0);

    shader->setFloat("global.iTime", time);
    shader->setVec3("iResolution", res);

    draw();
}

void Renderer::draw() {
   
    shader->use();
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
