#include <platform.h>

Platform::Platform(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) :
        PlainDynamicObject(ResourceManager::getSprite("platform"), pos, 0.0F, size * glm::vec2{5.0F, 1.0F}, color) {}

void Platform::onCollision(AbstractObject &object) {
    auto type = typeid(object).name();
    if (type == typeid(SolidBlock).name()) {
        alignToEdge(object);
    }
}

void Platform::regInput(const ContextHandler &context) {
    auto rightKey = context.getKey(GLFW_KEY_RIGHT);
    auto leftKey = context.getKey(GLFW_KEY_LEFT);

    if (rightKey == GLFW_PRESS && leftKey == GLFW_RELEASE) {
        setVel(glm::vec2{X_SPEED, 0.0F});
    } else if (rightKey == GLFW_RELEASE && leftKey == GLFW_PRESS) {
        setVel(glm::vec2{-X_SPEED, 0.0F});
    } else {
        setVel(glm::vec2{0.0F, 0.0F});
    }
}

void Platform::alignToEdge(AbstractObject &object) {
    auto x_overlap = std::abs(pos_.x - object.getPos().x) - (size_.x + object.getSize().x) / 2.0F;
    if (pos_.x > object.getPos().x) {
        x_overlap *= -1;
    }
    setPos(getPos() + glm::vec2{x_overlap, 0.0F});
}
