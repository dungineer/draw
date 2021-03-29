//
// Created by AlNov on 01.02.2021.
//

#ifndef DRAW_SHADER_H
#define DRAW_SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <filesystem>
#include <initializer_list>
#include <iostream>

class Shader {
public:
    Shader(const Shader &) = delete;

    Shader &operator=(const Shader &) = delete;

    Shader &operator=(Shader &&shader) noexcept {
        id_ = shader.id_;
        return *this;
    }

    Shader(const Shader &&shader) noexcept: id_(shader.id_) {}

    [[maybe_unused]] explicit Shader(const std::filesystem::path &vertexPath,
                                     const std::filesystem::path &fragmentPath);

    [[maybe_unused]] explicit Shader(const std::filesystem::path &vertexPath,
                                     const std::filesystem::path &geometryPath,
                                     const std::filesystem::path &fragmentPath);

    void use() const {
        glUseProgram(id_);
    }

    [[nodiscard]] unsigned int getID() const {
        return id_;
    }

    [[maybe_unused]] void setUniform(const std::string &uniform_name, GLint value) const {
        glUniform1i(glGetUniformLocation(id_, uniform_name.c_str()), value);
    }

    [[maybe_unused]] void setUniform(const std::string &uniform_name, GLfloat value) const {
        glUniform1f(glGetUniformLocation(id_, uniform_name.c_str()), value);
    }

    [[maybe_unused]] void setUniform(const std::string &uniform_name, const glm::vec2 &values) const {
        glUniform2f(glGetUniformLocation(id_, uniform_name.c_str()), values.x, values.y);
    }

    [[maybe_unused]] void setUniform(const std::string &uniform_name, const glm::vec3 &values) const {
        glUniform3f(glGetUniformLocation(id_, uniform_name.c_str()), values.x, values.y, values.z);
    }

    [[maybe_unused]] void setUniform(const std::string &uniform_name, const glm::vec4 &values) const {
        glUniform4f(glGetUniformLocation(id_, uniform_name.c_str()), values.x, values.y, values.z, values.w);
    }

    [[maybe_unused]] void setUniform(const std::string &uniform_name, const glm::mat4 &values) const {
        glUniformMatrix4fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, GL_FALSE, glm::value_ptr(values));
    }

private:
    unsigned int id_;

    static unsigned int compileShader(const std::filesystem::path &code, GLenum type);

    static unsigned int linkShaderProgram(const std::initializer_list<unsigned int> &shaders);
};


#endif //DRAW_SHADER_H
