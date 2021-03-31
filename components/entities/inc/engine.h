#ifndef DRAW_ENGINE_H
#define DRAW_ENGINE_H


#include <context_handler.h>
#include <plain_dynamic_object.h>

#include <unordered_set>
#include <memory>
#include <stack>


class Engine final {
public:
    Engine() = default;

    void poll();

    void addObjects(std::pair<std::vector<std::unique_ptr<PlainStaticObject>>,
            std::vector<std::unique_ptr<PlainDynamicObject>>> objects);

    void addStaticObject(std::unique_ptr<PlainStaticObject> static_object);

    void addDynamicObject(std::unique_ptr<PlainDynamicObject> dynamic_object);

    void regInput(const ContextHandler &context);

    void clear();

private:
    template<class T1, class T2>
    static void resolveCollision(const std::unique_ptr<T1> &obj1,
                                 const std::unique_ptr<T2> &obj2);

    std::unordered_set<std::unique_ptr<PlainStaticObject>> static_objects_{};

    std::unordered_set<std::unique_ptr<PlainDynamicObject>> dynamic_objects_{};
};


#endif //DRAW_ENGINE_H
