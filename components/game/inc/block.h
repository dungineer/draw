#ifndef DRAW_BLOCK_H
#define DRAW_BLOCK_H


#include <plain_static_object.h>
#include <resource_manager.h>
#include <colors.h>


class Block : public PlainStaticObject {
public:
    Block(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color);

// TODO Destroy when collision
    virtual void onCollision(AbstractObject &) override {}

    virtual ~Block() override {
        --counter;
    }

private:
    static size_t counter;
};

class SolidBlock : public PlainStaticObject {
public:
    explicit SolidBlock(const glm::vec2 &pos, const glm::vec2 &size);

// TODO Destroy when collision and double damage
    virtual void onCollision(AbstractObject &) override {}
};


#endif //DRAW_BLOCK_H
