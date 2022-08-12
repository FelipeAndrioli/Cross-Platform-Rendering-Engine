#include <iostream>

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"

#include "shader.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
  
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, 
            "Redering Engine.exe", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed initializing window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetWindowPos(window, 100, 100);

    const char *vert_shader = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/shader.vs";
    
    const char *frag_shader = "C:/Users/Felipe/Documents/current_projects/Cross-Platform-Rendering-Engine/src/shaders/shader.fs";

    Shader myShader = Shader(vert_shader, frag_shader, nullptr);

    float vertices[] = {
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 
        1.0f, -1.0f, 0.0f, 
        -1.0f, -1.0f, 0.0f
    };

    int indices[] = {
        0, 1, 2,
        0, 3, 2
    };

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT,  GL_FALSE, 3 * sizeof(float), 
            (void*)0); 
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 
            GL_STATIC_DRAW);

    glBindVertexArray(0);

    glm::vec3 iResolution = glm::vec3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
    myShader.use();
    myShader.setVec3("iResolution", iResolution);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        
        processInput(window);

        myShader.use();
        float iTime = glfwGetTime();
        myShader.setFloat("iTime", iTime);
    
        std::cout << "iTime -> " << iTime << std::endl; 

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    myShader.end();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glfwTerminate();

    return 0;
}









