#include "../include/window.h"

void Window::framebuffer_size_callback(GLFWwindow *t_window, int width, 
    int height) {
    // TODO
    // need to change the values of the window propertys as well
    glViewport(0, 0, width, height);
    glfwSetWindowSize(t_window, width, height);
    std::cout << "Width -> " << width << " Height -> " << height << std::endl;
}

void Window::key_callback(GLFWwindow *t_window, int key, int scancode, int action, 
    int mods) {
  
    if (key < 0) {
        return;
    }

    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(t_window, true);
    }

    switch(action) {
        case GLFW_PRESS:
            keyboard.keys[key].pressed = true;
            break;
        case GLFW_RELEASE:
            keyboard.keys[key].pressed = false;
            break;
        default:
            break;
    }
}

void Window::cursor_position_callback(GLFWwindow *t_window, double x_pos, 
    double y_pos) {
    
    std::cout << "x pos -> " << x_pos << " y pos -> " << y_pos << std::endl; 
}

Window::Window() {

}

Window::Window(void(*_init)(), void(*_update)(), void(*_destroy)()) {
    glfw_context_version_minor = 4;
    glfw_context_version_major = 4;
    opengl_profile = GLFW_OPENGL_CORE_PROFILE;

    window_name = "Rendering Engine.exe";
    window_width = 800;
    window_height = 600;
  
    clear_color_r = 0.5f;
    clear_color_g = 0.5f;
    clear_color_b = 0.5f;

    m_update = _update;
    m_init = _init;
    m_destroy = _destroy;

    for (int i = 0; i < GLFW_KEY_LAST; i++) {
        keyboard.keys[i].pressed = false;
    }
}

Window::~Window() {
    std::cout << "Destroying Window..." << std::endl;
    m_destroy();
    glfwTerminate();
    return;
}

void Window::window_create() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfw_context_version_minor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfw_context_version_major);
    glfwWindowHint(GLFW_OPENGL_PROFILE, opengl_profile);
    
    m_window = glfwCreateWindow(window_width, window_height, window_name, 
        nullptr, nullptr);

    if (m_window == nullptr) {
        std::cout << "Failed initializing window!" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return;
    }

    glViewport(0, 0, window_width, window_height);
    glfwSetWindowPos(m_window, 100, 100);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    m_init();
}

void Window::main_loop() {
    window_create();

    while(!glfwWindowShouldClose(m_window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(clear_color_r, clear_color_g, clear_color_b, 1.0f);
        
        m_update();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

    void Window::resize(int new_width, int new_height) {
    framebuffer_size_callback(m_window, new_width, new_height);
}

