#include "block.h"

size_t Block::counter = 0;

Block::Block(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) :
        PlainStaticObject(ResourceManager::getSprite("block"), pos, 0.0F, size, color) {
    ++counter;
}

SolidBlock::SolidBlock(const glm::vec2 &pos, const glm::vec2 &size) :
        PlainStaticObject(ResourceManager::getSprite("solid_block"), pos, 0.0F, size, Colors::NoColor) {}