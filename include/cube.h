
#ifndef DRAW_CUBE_H
#define DRAW_CUBE_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cube {
public:
    Cube(glm::vec3 pos, glm::vec4 clr, const Texture *tex) :
            color(clr),
            position(pos),
            model(glm::scale(glm::translate(glm::mat4(1.0f), pos), glm::vec3(1.0f))),
            texture(tex) {};

    static void staticInit(const GLfloat *vertices, GLuint64 ver_size, const GLuint *indices, GLuint64 ind_size);

    static void staticDeinit();

    void draw(GLuint program, const glm::mat4 &view, const glm::mat4 &projection) const;

    [[maybe_unused]] void setPos(glm::vec3);


    [[nodiscard]] glm::vec3 getPos() const { return position; }

    [[maybe_unused]] void setModel(const glm::mat4 &);

    [[nodiscard]] const glm::mat4 &getModel() const { return model; }

public:
    glm::vec4 color;
    glm::vec3 position;
    glm::mat4 model;
    const Texture *texture;

    static GLuint VBO;
    static GLuint EBO;
    static GLuint VAO;
};

GLuint Cube::VBO = 0;
GLuint Cube::EBO = 0;
GLuint Cube::VAO = 0;

void Cube::staticInit(const GLfloat *vertices, GLuint64 ver_size, const GLuint *indices, GLuint64 ind_size) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, ver_size, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::draw(GLuint program, const glm::mat4 &view, const glm::mat4 &projection) const {
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);

    if(texture != nullptr) {
        texture->use(program);
    }

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Cube::staticDeinit() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cube::setPos(glm::vec3 newPos) {
    position = newPos;
    model = glm::translate(glm::mat4(1.0f), newPos);
}

void Cube::setModel(const glm::mat4 &_model) {
    model = _model;
}


#endif //DRAW_CUBE_H
