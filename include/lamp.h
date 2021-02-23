
#ifndef DRAW_LAMP_H
#define DRAW_LAMP_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Lamp {
public:
    Lamp(glm::vec3 pos, glm::vec3 clr, GLuint number) :
            position(pos),
            color(clr),
            formName("pointLights[" + std::to_string(number) + "]"),
            model(glm::scale(glm::translate(glm::mat4(1.0f), pos), glm::vec3(0.2f))) {
        lampUniform.position = formName + ".position";

        lampUniform.constant = formName + ".constant";
        lampUniform.linear = formName + ".linear";
        lampUniform.quadratic = formName + ".quadratic";

        lampUniform.ambient = formName + ".ambient";
        lampUniform.diffuse = formName + ".diffuse";
        lampUniform.specular = formName + ".specular";
    };

    static void staticInit(const GLfloat *vertices, GLuint64 ver_size, const GLuint *indices, GLuint64 ind_size);

    static void staticDeinit();

    void draw(GLuint program, const glm::mat4 &view, const glm::mat4 &projection) const;

    void use(GLuint program,  const Camera &) const;

    [[maybe_unused]] void setPos(glm::vec3 &&);

    [[nodiscard]] glm::vec3 getPos() const { return position; }

private:
    struct {
        std::string position;

        std::string constant;
        std::string linear;
        std::string quadratic;

        std::string ambient;
        std::string diffuse;
        std::string specular;
    } lampUniform;

    glm::vec3 position;
    glm::vec3 color;
    glm::mat4 model;

    std::string formName;

    static GLuint VBO;
    static GLuint EBO;
    static GLuint VAO;
};

GLuint Lamp::VBO = 0;
GLuint Lamp::EBO = 0;
GLuint Lamp::VAO = 0;

void Lamp::staticInit(const GLfloat *vertices, GLuint64 ver_size, const GLuint *indices, GLuint64 ind_size) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, ver_size, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)nullptr);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Lamp::draw(GLuint program, const glm::mat4 &view, const glm::mat4 &projection) const {
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(program, "lightColor"), color.x, color.y, color.z);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Lamp::staticDeinit() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Lamp::setPos(glm::vec3 &&newPos) {
    position = newPos;
    model = glm::translate(glm::mat4(1.0f), newPos);
}

void Lamp::use(GLuint program, const Camera &camera) const {
    glUniform3f(glGetUniformLocation(program, lampUniform.position.c_str()), position.x, position.y, position.z);

    glUniform3f(glGetUniformLocation(program, lampUniform.ambient.c_str()), color.r / 5, color.g / 5, color.b / 5);
    glUniform3f(glGetUniformLocation(program, lampUniform.diffuse.c_str()), color.r / 2, color.g / 2, color.b / 2);
    glUniform3f(glGetUniformLocation(program, lampUniform.specular.c_str()), color.r / 1, color.g / 1, color.b / 1);

    glUniform1f(glGetUniformLocation(program, lampUniform.constant.c_str()),  1.0f);
    glUniform1f(glGetUniformLocation(program, lampUniform.linear.c_str()),  0.09f);
    glUniform1f(glGetUniformLocation(program, lampUniform.quadratic.c_str()), 0.032f);
}


#endif //DRAW_LAMP_H
