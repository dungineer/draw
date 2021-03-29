#ifndef DRAW_RESOURCE_MANAGER_H
#define DRAW_RESOURCE_MANAGER_H


#include <shader.h>
#include <texture.h>

#include <unordered_map>


class ResourceManager {
public:
    void loadShader(Shader shader, const std::string &name) {
        (void) shaders_.emplace(name, std::move(shader));
    }

    void loadTexture(Texture2D texture, const std::string &name) {
        (void) textures_.emplace(name, std::move(texture));
    }

    const Shader &getShader(const std::string &name) {
        return shaders_.at(name);
    }

    const Texture2D &getTexture(const std::string &name) {
        return textures_.at(name);
    }

    static ResourceManager &instance() {
        static ResourceManager instance{};
        return instance;
    }

private:
    ResourceManager() = default;

    std::unordered_map<std::string, Texture2D> textures_{};
    std::unordered_map<std::string, Shader> shaders_{};
};


#endif //DRAW_RESOURCE_MANAGER_H
