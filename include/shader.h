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

    Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {

        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vertexFile;
        std::ifstream fragmentFile;

        vertexFile.exceptions(std::ifstream::badbit);
        fragmentFile.exceptions(std::ifstream::badbit);
        try {
            vertexFile.open(vertexPath);
            fragmentFile.open(fragmentPath);
            std::stringstream vShaderStream;
            std::stringstream fShaderStream;

            vShaderStream << vertexFile.rdbuf();
            fShaderStream << fragmentFile.rdbuf();

            vertexFile.close();
            fragmentFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure & e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        } catch (...) {
            std::cout << "ERROR::SHADER::UNKNOWN_ARRAY" << std::endl;
        }

        const GLchar *vShaderCode = vertexCode.c_str();
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
        glAttachShader(program, fragment);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(this->program, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() const {
        glUseProgram(program);
    }
};


#endif //DRAW_SHADER_H
