#ifndef DRAW_PLAIN_STATIC_OBJECT_H
#define DRAW_PLAIN_STATIC_OBJECT_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <sprite.h>
#include <abstract_object.h>

#include <memory>


class PlainStaticObject : public AbstractObject {
public:
    PlainStaticObject(std::shared_ptr<Sprite> sprite,
                      const glm::vec2 &pos,
                      float rotate = 0.0F,
                      const glm::vec2 &size = glm::vec2(1.0F),
                      const glm::vec4 &color = glm::vec4(1.0F));

    virtual void draw() const override;

    void setColor(const glm::vec4 &color);

    [[nodiscard]] const glm::vec2 &getColor() const {
        return size_;
    }

    [[nodiscard]] glm::vec2 getPos() const override {
        return pos_;
    }

    [[nodiscard]] float getRotate() const {
        return rotate_;
    }

    [[nodiscard]] glm::vec2 getSize() const override {
        return size_;
    }

    virtual std::shared_ptr<Sprite> getSprite() {
        return sprite_;
    }

protected:
    void updateModel();

    std::shared_ptr<Sprite> sprite_{};

    glm::vec2 pos_{};
    float rotate_;
    glm::vec2 size_{};

    glm::vec4 color_{};

    glm::mat4 model_{};
};


#endif //DRAW_PLAIN_STATIC_OBJECT_H
