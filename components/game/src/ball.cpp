#include <ball.h>

Ball::Ball(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) :
        PlainDynamicObject(ResourceManager::getSprite("ball"), pos, 0.0F, size, color) {}

void Ball::onCollision(AbstractObject &object) {
    auto type = typeid(object).name();
    if (type == typeid(SolidBlock).name()) {
        reflectFrom(dynamic_cast<SolidBlock &>(object));
    } else if (type == typeid(Block).name()) {
        reflectFrom(dynamic_cast<Block &>(object));
        object.setDeleted();
    } else if (type == typeid(Platform).name()) {
        reflectFrom(dynamic_cast<Platform &>(object));
    }
}

void Ball::reflectFrom(AbstractObject &object) {
    auto x_overlap = std::abs(pos_.x - object.getPos().x) - (size_.x + object.getSize().x) / 2.0F;
    auto y_overlap = std::abs(pos_.y - object.getPos().y) - (size_.y + object.getSize().y) / 2.0F;

    if (x_overlap < y_overlap) {
        if (pos_.y > object.getPos().y) {
            y_overlap *= -1;
        }

        setVel(getVel() * glm::vec2{1.0F, -1.0F});
        setPos(getPos() + glm::vec2{0.0F, y_overlap});
    } else {
        if (pos_.x > object.getPos().x) {
            x_overlap *= -1;
        }

        setVel(getVel() * glm::vec2{-1.0F, 1.0F});
        setPos(getPos() + glm::vec2{x_overlap, 0.0F});
    }
}

void Ball::reflectFrom(Platform &object) {
    auto x_overlap = std::abs(pos_.x - object.getPos().x) - (size_.x + object.getSize().x) / 2.0F;
    auto y_overlap = std::abs(pos_.y - object.getPos().y) - (size_.y + object.getSize().y) / 2.0F;

    if (x_overlap < y_overlap) {
        setPos(getPos() + glm::vec2{0.0F, -y_overlap});
        auto vel_vec = glm::normalize(glm::vec2{pos_ - object.getPos()});
        setVel(vel_vec * glm::length(getVel()));
    } else {
        if (pos_.x > object.getPos().x) {
            x_overlap *= -1;
        }
        setVel(getVel() * glm::vec2{-1.0F, 1.0F});
        setPos(getPos() + glm::vec2{x_overlap, 0.0F});
    }
}
