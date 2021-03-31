#include <plain_static_object.h>


PlainStaticObject::PlainStaticObject(
        std::shared_ptr<Sprite> sprite,
        const glm::vec2 &pos,
        float rotate,
        const glm::vec2 &size,
        const glm::vec4 &color
) : pos_(pos),
    rotate_(rotate),
    size_(size),
    sprite_(std::move(sprite)),
    color_(color) {
    updateModel();
}

void PlainStaticObject::draw() const {
    int curr_program = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &curr_program);

    glUniformMatrix4fv(glGetUniformLocation(curr_program, "model"), 1, GL_FALSE, glm::value_ptr(model_));
    glUniform4f(glGetUniformLocation(curr_program, "custom_color"), color_.r, color_.g, color_.b, color_.a);

    sprite_->draw();
}

void PlainStaticObject::updateModel() {
    auto model = glm::mat4(1.0F);

    model = glm::translate(model, glm::vec3(pos_, 0.0F));

    model = glm::rotate(model, glm::radians(rotate_), glm::vec3(0.0F, 0.0F, 1.0F));
    model = glm::translate(model, glm::vec3(-0.5F * size_.x, -0.5F * size_.y, 0.0F));

    model = glm::scale(model, glm::vec3(size_, 1.0F));

    model_ = model;
}

void PlainStaticObject::setColor(const glm::vec4 &color) {
    color_ = color;
}



