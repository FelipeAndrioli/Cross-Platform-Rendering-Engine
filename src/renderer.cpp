#include "../include/renderer.h"

Renderer::Renderer(Scene *CurrentScene) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, CurrentScene->vertices.size() * 
        sizeof(float), &CurrentScene->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, CurrentScene->indices.size() * 
        sizeof(unsigned int), &CurrentScene->indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Renderer::update(Scene *CurrentScene, float time) {

    glm::vec3 res = glm::vec3(800, 600, 0);

    CurrentScene->SceneShader->setFloat("global.iTime", time);
    CurrentScene->SceneShader->setVec3("iResolution", res);
}

void Renderer::draw(Scene *CurrentScene) {
   
    CurrentScene->SceneShader->use();
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, sizeof(CurrentScene->indices.size()), GL_UNSIGNED_INT, 0);
}
