#include <context_handler.h>

ContextHandler::ContextHandler(const std::string &title, int SCREEN_WIDTH, int SCREEN_HEIGHT) :
        screen_height_(static_cast<float>(SCREEN_HEIGHT)),
        screen_width_(static_cast<float>(SCREEN_WIDTH)) {
    // glfw setup
    if (GLFW_TRUE != glfwInit()) {
        throw std::runtime_error("ERROR::GLFW::INIT_FAILED");
    }

    // Minimum  OpenGl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 1);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    window_ = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str(), nullptr, nullptr);

    if (nullptr == window_) {
        throw std::runtime_error("ERROR::GLFW::WINDOW_CREATE_FAILED");
    }

    glfwMakeContextCurrent(window_);

    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetCursorPos(window_,
                     static_cast<const float>(SCREEN_WIDTH) / 2.0F,
                     static_cast<const float>(SCREEN_HEIGHT) / 2.0F);

    // glew setup
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit()) {
        throw std::runtime_error("ERROR::GLEW::INIT_FAILED");
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    std::cout << "CONTEXT::INIT_SUCCESS" << std::endl;
}