// Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

// Components
#include <resource_manager.h>

// C++
#include <iostream>

static const int screenWidth = 1200;
static const int screenHeight = 800;

static GLFWwindow *setup_gl();

int main() {
    auto window = setup_gl();

    ResourceManager::instance().loadTexture(
            Texture2D("textures/fond.png", "diffuseMap"), "fond");

    ResourceManager::instance().loadShader(
            Shader("shaders/vertex.glsl", "shaders/fragment.glsl"), "draw");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

// TODO: wrap this
static GLFWwindow *setup_gl() {
    // glfw setup
    if (GLFW_TRUE != glfwInit()) {
        std::cerr << "GLFW::Error::Init_Failed" << std::endl;
        throw std::exception("GLFW::Error::Init_Failed");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 1);

    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "BBBreakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPos(window,
                     static_cast<const float>(screenWidth) / 2.0F,
                     static_cast<const float>(screenHeight) / 2.0F);

    // glew setup
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        std::cerr << "GLEW::Error::Init_Failed" << std::endl;
        throw std::exception("GLEW::Error::Init_Failed");
    }

    // OpenGL options
    glViewport(0, 0, screenWidth, screenHeight);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    return window;
}
