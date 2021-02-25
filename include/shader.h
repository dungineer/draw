//
// Created by AlNov on 01.02.2021.
//

#ifndef DRAW_SHADER_H
#define DRAW_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>


class Shader {
public:
    GLuint program;

    Shader(const GLchar *vertexPath, const GLchar *geometryPath, const GLchar *fragmentPath) {

        std::string vertexCode;
        std::string geometryCode;
        std::string fragmentCode;

        std::ifstream vertexFile;
        std::ifstream geometryFile;
        std::ifstream fragmentFile;

        vertexFile.exceptions(std::ifstream::badbit);
        geometryFile.exceptions(std::ifstream::badbit);
        fragmentFile.exceptions(std::ifstream::badbit);

        if (vertexPath != nullptr) {
            try {
                vertexFile.open(vertexPath);
                std::stringstream vShaderStream;
                vShaderStream << vertexFile.rdbuf();
                vertexFile.close();
                vertexCode = vShaderStream.str();
            } catch (std::ifstream::failure &e) {
                std::cout << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            } catch (...) {
                std::cout << "ERROR::SHADER::VERTEX::UNKNOWN_ERROR" << std::endl;
            }
        }

        if (geometryPath != nullptr) {
            try {
                geometryFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << geometryFile.rdbuf();
                geometryFile.close();
                geometryCode = gShaderStream.str();
            } catch (std::ifstream::failure &e) {
                std::cout << "ERROR::SHADER::GEOMETRY::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            } catch (...) {
                std::cout << "ERROR::SHADER::GEOMETRY::UNKNOWN_ERROR" << std::endl;
            }
        }

        if (fragmentPath != nullptr) {
            try {
                fragmentFile.open(fragmentPath);
                std::stringstream fShaderStream;
                fShaderStream << fragmentFile.rdbuf();
                fragmentFile.close();
                fragmentCode = fShaderStream.str();
            } catch (std::ifstream::failure &e) {
                std::cout << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            } catch (...) {
                std::cout << "ERROR::SHADER::FRAGMENT::UNKNOWN_ARRAY" << std::endl;
            }
        }

        const GLchar *vShaderCode = vertexCode.c_str();
        const GLchar *gShaderCode = geometryCode.c_str();
        const GLchar *fShaderCode = fragmentCode.c_str();

        GLint success;

        GLuint vertex;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        GLuint geometry;
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, nullptr);
        glCompileShader(geometry);

        glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(geometry, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        GLuint fragment;
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        program = glCreateProgram();
        glAttachShader(program, vertex);
        if (geometryPath != nullptr) {
            glAttachShader(program, geometry);
        }
        glAttachShader(program, fragment);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(this->program, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(geometry);
        glDeleteShader(fragment);
    }

    void use() const {
        glUseProgram(program);
    }

    void setUniform(const std::string &uniform_name, GLfloat value) const {
        glUniform1f(glGetUniformLocation(program, uniform_name.c_str()), value);
    }

    void setUniform(const std::string &uniform_name, glm::vec2 values) const {
        glUniform2f(glGetUniformLocation(program, uniform_name.c_str()), values.x, values.y);
    }

    void setUniform(const std::string &uniform_name, glm::vec3 values) const {
        glUniform3f(glGetUniformLocation(program, uniform_name.c_str()), values.x, values.y, values.z);
    }
};


#endif //DRAW_SHADER_H
