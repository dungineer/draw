#include <engine.h>


void Engine::poll() {
    for (auto &d_object : dynamic_objects_) {
        d_object->move();

        for (auto &s_obj : static_objects_) {
            resolveCollision(d_object, s_obj);
        }

        for (auto &d_obj : dynamic_objects_) {
            if (d_obj != d_object) {
                resolveCollision(d_object, d_obj);
            }
        }
    }

    std::erase_if(static_objects_, [](auto &it) { return it->isDeleted(); });

    std::for_each(static_objects_.begin(), static_objects_.end(), [](auto &s_obj) { s_obj->draw(); });
    std::for_each(dynamic_objects_.begin(), dynamic_objects_.end(), [](auto &d_obj) { d_obj->draw(); });
}

void Engine::addObjects(std::pair<
        std::vector<std::unique_ptr<PlainStaticObject>>,
        std::vector<std::unique_ptr<PlainDynamicObject>>> objects) {

    for (auto &object : objects.first) {
        static_objects_.emplace(std::move(object));
    }

    for (auto &object : objects.second) {
        dynamic_objects_.emplace(std::move(object));
    }
}

void Engine::addStaticObject(std::unique_ptr<PlainStaticObject> static_object) {
    static_objects_.emplace(std::move(static_object));
}

void Engine::addDynamicObject(std::unique_ptr<PlainDynamicObject> dynamic_object) {
    dynamic_objects_.emplace(std::move(dynamic_object));
}

// TODO Implement hitboxes
template<class T1, class T2>
void Engine::resolveCollision(const std::unique_ptr<T1> &obj1,
                              const std::unique_ptr<T2> &obj2) {
    if (std::abs(obj1->getPos().x - obj2->getPos().x) < (obj1->getSize().x + obj2->getSize().x) / 2.0F &&
        std::abs(obj1->getPos().y - obj2->getPos().y) < (obj1->getSize().y + obj2->getSize().y) / 2.0F) {
        obj1->onCollision(*obj2);
    }
}

void Engine::regInput(const ContextHandler &context) {
    std::for_each(static_objects_.begin(), static_objects_.end(), [&context](auto &s_obj) { s_obj->regInput(context); });
    std::for_each(dynamic_objects_.begin(), dynamic_objects_.end(), [&context](auto &d_obj) { d_obj->regInput(context); });
}

void Engine::clear() {
    dynamic_objects_.clear();
    static_objects_.clear();
}
