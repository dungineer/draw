
#ifndef DRAW_TEXTURE_H
#define DRAW_TEXTURE_H

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <shader.h>

#include <filesystem>
#include <iostream>


class Texture2D {
public:
    Texture2D(const Texture2D &) = delete;

    Texture2D &operator=(const Texture2D &) = delete;

    Texture2D &operator=(Texture2D &&texture) noexcept = default;

    Texture2D(Texture2D &&) noexcept = default;

    [[maybe_unused]] explicit Texture2D(const std::filesystem::path &diffuse_path, const std::string &diffuse_name) {
        (void) textures_.emplace_back(loadImage_(diffuse_path), diffuse_name);
    }

    [[maybe_unused]] explicit Texture2D(const std::filesystem::path &diffuse_path, const std::string &diffuse_name,
                                        const std::filesystem::path &normals_path, const std::string &normals_name) {
        (void) textures_.emplace_back(loadImage_(diffuse_path), diffuse_name);
        (void) textures_.emplace_back(loadImage_(normals_path), normals_name);
    }

    [[maybe_unused]] explicit Texture2D(const std::filesystem::path &diffuse_path, const std::string &diffuse_name,
                                        const std::filesystem::path &normals_path, const std::string &normals_name,
                                        const std::filesystem::path &parallax_path, const std::string &parallax_name) {
        (void) textures_.emplace_back(loadImage_(diffuse_path), diffuse_name);
        (void) textures_.emplace_back(loadImage_(normals_path), normals_name);
        (void) textures_.emplace_back(loadImage_(parallax_path), parallax_name);
    }

    void use() const;

private:
    static unsigned int loadImage_(const std::filesystem::path &tex_path);

    std::vector<std::pair<int, std::string>> textures_;
};


#endif //DRAW_TEXTURE_H
