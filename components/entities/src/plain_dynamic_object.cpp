#include "plain_dynamic_object.h"

void PlainDynamicObject::setPos(const glm::vec2 &pos) {
    pos_ = pos;
    updateModel();
}

void PlainDynamicObject::setRotate(float rotate) {
    rotate_ = rotate;
    updateModel();
}

void PlainDynamicObject::setSize(const glm::vec2 &size) {
    size_ = size;
    updateModel();
}

void PlainDynamicObject::setVel(const glm::vec2 &vel) {
    vel_ = vel;
}

void PlainDynamicObject::setAngVel(float ang_vel) {
    rotate_vel_ = ang_vel;
}

glm::vec2 PlainDynamicObject::move() {
    setPos(pos_ + vel_);
    return pos_;
}
