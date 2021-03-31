#ifndef DRAW_PLAIN_DYNAMIC_OBJECT_H
#define DRAW_PLAIN_DYNAMIC_OBJECT_H


#include <plain_static_object.h>


class PlainDynamicObject : public PlainStaticObject {
public:
    using PlainStaticObject::PlainStaticObject;

    virtual glm::vec2 move();

    void setPos(const glm::vec2 &pos);

    void setSize(const glm::vec2 &size);

    void setRotate(float rotate);

    void setVel(const glm::vec2 &vel);

    [[nodiscard]] glm::vec2 getVel() const {
        return vel_;
    }

    virtual void setAngVel(float ang_vel);

    [[nodiscard]] float getAngVel() const {
        return rotate_vel_;
    }

private:
    glm::vec2 vel_{};
    float rotate_vel_;
};


#endif //DRAW_PLAIN_DYNAMIC_OBJECT_H
