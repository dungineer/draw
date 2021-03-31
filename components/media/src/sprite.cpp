#include <sprite.h>


void Sprite::draw() const {
    texture_->use();
    shape_->draw();
}
