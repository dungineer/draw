#ifndef DRAW_RESOURCE_MANAGER_H
#define DRAW_RESOURCE_MANAGER_H


#include <texture.h>
#include <abstract_shape.h>
#include <quad_shape.h>
#include <sprite.h>

#include <memory>
#include <unordered_map>


class ResourceManager {
public:
    static void loadShader(Shader shader, const std::string &name) {
        instance().shaders_.emplace(name, std::make_shared<Shader>(std::move(shader)));
    }

    static std::shared_ptr<Shader> getShader(const std::string &name) {
        return instance().shaders_.at(name);
    }

    static void loadTexture(Texture2D texture, const std::string &name) {
        instance().textures_.emplace(name, std::make_shared<Texture2D>(std::move(texture)));
    }

    static std::shared_ptr<Texture2D> getTexture(const std::string &name) {
        return instance().textures_.at(name);
    }

    static void loadShape(std::shared_ptr<AbstractShape> shape, const std::string &name) {
        instance().shapes_.emplace(name, std::move(shape));
    }

    static std::shared_ptr<AbstractShape> getShape(const std::string &name) {
        return instance().shapes_.at(name);
    }

    static void buildSprite(const std::string &shape_name,
                            const std::string &tex_name,
                            const std::string &sprite_name) {
        instance().sprites_.emplace(
                sprite_name,
                std::make_shared<Sprite>(getShape(shape_name), getTexture(tex_name))
        );
    }

    static std::shared_ptr<Sprite> getSprite(const std::string &name) {
        return instance().sprites_.at(name);
    }

private:
    ResourceManager() = default;

    static ResourceManager &instance() {
        static ResourceManager instance{};
        return instance;
    }

    std::unordered_map<std::string, std::shared_ptr<Texture2D>> textures_{};
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_{};
    std::unordered_map<std::string, std::shared_ptr<AbstractShape>> shapes_{};
    std::unordered_map<std::string, std::shared_ptr<Sprite>> sprites_{};
};


#endif //DRAW_RESOURCE_MANAGER_H
