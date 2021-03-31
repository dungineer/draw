
#ifndef DRAW_TEXTURE_H
#define DRAW_TEXTURE_H

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <shader.h>

#include <filesystem>
#include <iostream>
#include <string>


class Texture2D {
public:
    Texture2D(const Texture2D &) = delete;

    Texture2D &operator=(Texture2D &&tex) noexcept = default;

    Texture2D(Texture2D &&) noexcept = default;

    explicit Texture2D(const std::filesystem::path &tex_path) {
        textures_.emplace_back(loadImage_(tex_path), uniform_name);
    }

    void use() const;

private:
    static constexpr char uniform_name[] = "diffuseMap";

    static unsigned int loadImage_(const std::filesystem::path &tex_path);

    std::vector<std::pair<int, std::string>> textures_{};
};


#endif //DRAW_TEXTURE_H
