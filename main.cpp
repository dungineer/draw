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
#include "object.h"

static const GLint screen_width = 1200;
static const GLint screen_height = 800;

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

GLfloat post_vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f
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

//    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(0.2f, 0.3f, 0.1f, 1.0f);

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
}

int main() {
    GLFWwindow *window = setup_glfw();
    setup_gl();

    global_camera = new Camera({0.0f, 0.0f, 3.0f}, screen_width, screen_height);

    Camera &camera = *global_camera;
    Shader shader("shaders/vertex.shader", "shaders/fragment.shader");
    Shader shader_lamp("shaders/vertex_lamp.shader", "shaders/fragment_lamp.shader");
    Shader render_shader("shaders/vertex_render.shader", "shaders/fragment_render.shader");

    Lamp::staticInit(vertices_lamp, sizeof(vertices_lamp), indices, sizeof(indices));
    Lamp lamp(glm::vec3(0.0f, 3.0f, -3.0f), glm::vec3(0.711f, 0.815f, 0.894f), 0);
    Lamp lamp1(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.711f, 0.815f, 0.894f), 1);
    DirLamp dir_lamp(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.711f, 0.815f, 0.894f), 0);

    Model model("models/backpack/backpack.obj");
    Object back1(glm::vec3(0.0f), &model);
    Object back2(glm::vec3(5.0f, 0.0f, 0.0f), &model);
    Object back3(glm::vec3(5.0f, 0.0f, 5.0f), &model);

    GLdouble t = glfwGetTime();
    GLdouble tt = glfwGetTime();

    // Frame
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    // FrameTex
    GLuint texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    // FrameRender
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screen_width, screen_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // 1
        shader.use();
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glClearColor(0.2f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        camera.update(shader);

        lamp.use(shader);
        lamp1.use(shader);
        dir_lamp.use(shader);

        back1.Draw(shader, camera);
        back2.Draw(shader, camera);
        back3.Draw(shader, camera);

        shader_lamp.use();

        // 2
        render_shader.use();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //
        GLuint quadVAO = 0;
        GLuint quadVBO = 0;

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);

        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(post_vertices), &post_vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        //
        glBindVertexArray(quadVAO);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);

        // FPS
        if (glfwGetTime() - tt > 1) {
            std::cout << "FPS: " << 1 / (glfwGetTime() - t) << std::endl;
            tt = glfwGetTime();
        }
        t = glfwGetTime();

        glfwSwapBuffers(window);
    }

    Lamp::staticDeinit();

    glfwTerminate();
    return 0;
}
