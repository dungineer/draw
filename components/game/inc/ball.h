#ifndef DRAW_BALL_H
#define DRAW_BALL_H


#include <platform.h>
#include <plain_dynamic_object.h>
#include <block.h>
#include <resource_manager.h>
#include <colors.h>

#include <typeinfo>


// TODO Find ball tex and shape
class Ball : public PlainDynamicObject {
public:
    Ball(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color = Colors::NoColor);

    virtual void onCollision(AbstractObject &object) override;

protected:
    void reflectFrom(AbstractObject &object);
};


#endif //DRAW_BALL_H
