#ifndef DRAW_CONTEXT_HANDLER_H
#define DRAW_CONTEXT_HANDLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>


class ContextHandler {
public:
    ContextHandler(const std::string &title, int screenWidth, int screenHeight);

    ~ContextHandler() {
        glfwTerminate();
    }

    [[nodiscard]] bool isOk() const {
        return !glfwWindowShouldClose(window_);
    }

    void update() const {
        glfwPollEvents();
        glfwSwapBuffers(window_);
    }

    [[nodiscard]] GLFWwindow *getWindow() const {
        return window_;
    }

    [[nodiscard]] int getKey(int key) const {
        return glfwGetKey(window_, key);
    }

    [[nodiscard]] float getWidth() const {
        return screen_width_;
    }

    [[nodiscard]] float getHeight() const {
        return screen_height_;
    }

private:
    const float screen_width_;
    const float screen_height_;

    GLFWwindow *window_;
};


#endif //DRAW_CONTEXT_HANDLER_H
