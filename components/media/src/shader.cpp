#include <shader.h>

#include <iostream>
#include <fstream>
#include <sstream>


[[maybe_unused]] Shader::Shader(const std::filesystem::path &vertexPath,
                                const std::filesystem::path &fragmentPath) {

    unsigned int vertexID = compileShader(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentID = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
    id_ = linkShaderProgram({vertexID, fragmentID});
}

[[maybe_unused]] Shader::Shader(const std::filesystem::path &vertexPath,
                                const std::filesystem::path &geometryPath,
                                const std::filesystem::path &fragmentPath) {

    unsigned int vertexID = compileShader(vertexPath, GL_VERTEX_SHADER);
    unsigned int geometryID = compileShader(geometryPath, GL_GEOMETRY_SHADER);
    unsigned int fragmentID = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
    id_ = linkShaderProgram({vertexID, geometryID, fragmentID});
}

unsigned int Shader::compileShader(const std::filesystem::path &shaderPath, GLenum type) {
    // Read shader
    std::string code{};
    try {
        std::ifstream file(shaderPath);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    } catch (std::exception &e) {
        std::cout << "ERROR::SHADER " << e.what() << shaderPath << std::endl;
    }

    // Compile shader
    unsigned int id = glCreateShader(type);

    const char *c = code.c_str();
    glShaderSource(id, 1, &c, nullptr);
    glCompileShader(id);

    int ok = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED " << infoLog << std::endl;
    }

    return id;
}

unsigned int Shader::linkShaderProgram(const std::initializer_list<unsigned int> &shaders) {
    unsigned int id = glCreateProgram();

    for (auto shader : shaders) {
        glAttachShader(id, shader);
    }

    glLinkProgram(id);

    int ok = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &ok);
    if (!ok) {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED " << infoLog << std::endl;
    }

    for (auto shader : shaders) {
        glDeleteShader(shader);
    }

    return id;
}
