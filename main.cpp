#include <iostream>
#include <cmath>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "lamp.h"
#include "model.h"
#include "texture.h"
#include "object.h"

static const GLint screen_width = 1600;
static const GLint screen_height = 1200;

Camera *global_camera = nullptr;

GLfloat vertices_lamp[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f
};

GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    global_camera->keyboard(key, action);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    global_camera->cursor(xpos, ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    global_camera->scroll(yoffset);
}

static GLFWwindow *setup_glfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "OpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPos(window, (float) screen_width / 2, (float) screen_height / 2);

    return window;
}

static void setup_gl() {
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, screen_width, screen_height);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main() {
    GLFWwindow *window = setup_glfw();
    setup_gl();

    global_camera = new Camera({0.0f, 0.0f, 3.0f}, screen_width, screen_height);

    Camera &camera = *global_camera;
    Shader shader("shaders/vertex.shader", "shaders/fragment.shader");
    Shader shader_lamp("shaders/vertex_lamp.shader", "shaders/fragment_lamp.shader");

    Lamp::staticInit(vertices_lamp, sizeof(vertices_lamp), indices, sizeof(indices));
    Lamp lamp(glm::vec3(0.0f, 3.0f, -3.0f), glm::vec3(0.711f, 0.815f, 0.894f), 0);
    Lamp lamp1(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.711f, 0.815f, 0.894f), 1);
    DirLamp lamp2(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.711f, 0.815f, 0.894f), 0);

    Model model("models/backpack/backpack.obj");
    Object back1(glm::vec3(0.0f), &model);
    Object back2(glm::vec3(5.0f, 0.0f, 0.0f), &model);
    Object back3(glm::vec3(5.0f, 0.0f, 5.0f), &model);

    GLdouble t = glfwGetTime();
    GLdouble tt = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        camera.update(shader);
        lamp.use(shader);
        lamp1.use(shader);
        lamp2.use(shader);
        back1.Draw(shader, camera);
        back2.Draw(shader, camera);
        back3.Draw(shader, camera);

        shader_lamp.use();
        lamp.draw(shader_lamp.program, camera.getView(), camera.getProjection());
        lamp1.draw(shader_lamp.program, camera.getView(), camera.getProjection());

        // FPS
        if (glfwGetTime() - tt > 2) {
            std::cout << "FPS: " << 1 / (glfwGetTime() - t) << std::endl;
            tt = glfwGetTime();
        }
        t = glfwGetTime();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
