#ifndef DRAW_PLATFORM_H
#define DRAW_PLATFORM_H


#include <context_handler.h>
#include <plain_dynamic_object.h>
#include <block.h>
#include <resource_manager.h>
#include <colors.h>


class Platform : public PlainDynamicObject {
public:
    Platform(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color = Colors::NoColor);

    virtual void onCollision(AbstractObject &object) override;

    virtual void regInput(const ContextHandler &context) override;

private:
    virtual void alignToEdge(AbstractObject &object);

    static constexpr float X_SPEED = 4.0F;
};


#endif //DRAW_PLATFORM_H
