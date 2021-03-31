#ifndef DRAW_ABSTRACT_OBJECT_H
#define DRAW_ABSTRACT_OBJECT_H


#include <context_handler.h>

#include <vector>
#include <functional>


class AbstractObject {
public:
    virtual void draw() const = 0;

    [[nodiscard]] virtual glm::vec2 getPos() const = 0;

    [[nodiscard]] virtual glm::vec2 getSize() const = 0;

    virtual void onCollision(AbstractObject &object) = 0;

    virtual void regInput(const ContextHandler &) {}

    virtual ~AbstractObject() = default;

    void setDeleted() {
        deleted_ = true;
    }

    [[nodiscard]] bool isDeleted() const {
        return deleted_;
    }

private:
    bool deleted_ = false;
};


#endif //DRAW_ABSTRACT_OBJECT_H
