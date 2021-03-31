#ifndef DRAW_SPRITE_H
#define DRAW_SPRITE_H


#include <glm/glm.hpp>

#include <texture.h>
#include <abstract_shape.h>

#include <memory>


class Sprite {
public:
    Sprite(const Sprite &) = delete;

    Sprite &operator=(Sprite &&texture) noexcept = default;

    Sprite(Sprite &&) noexcept = default;

    Sprite(std::shared_ptr<AbstractShape> shape, std::shared_ptr<Texture2D> texture) :
            shape_(std::move(shape)),
            texture_(std::move(texture)) {}

    virtual void draw() const;

private:
    std::shared_ptr<AbstractShape> shape_{};
    std::shared_ptr<Texture2D> texture_{};
};


#endif //DRAW_SPRITE_H
