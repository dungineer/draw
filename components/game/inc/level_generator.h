#ifndef DRAW_LEVEL_GENERATOR_H
#define DRAW_LEVEL_GENERATOR_H


#include <block.h>
#include <plain_dynamic_object.h>
#include <colors.h>

#include <memory>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>


class LevelGenerator {
public:
    LevelGenerator(float left, float right, float top, float bottom) :
            left_(left),
            right_(right),
            top_(top),
            bottom_(bottom) {}

    LevelGenerator(LevelGenerator &&) noexcept = default;

    LevelGenerator &operator=(LevelGenerator &&) noexcept = default;

    void loadLevel(const std::filesystem::path &levelPath);

    std::pair<std::vector<std::unique_ptr<PlainStaticObject>>, std::vector<std::unique_ptr<PlainDynamicObject>>>
    generateObjects(int stage);

private:
    static void getObject(char symbol, const glm::vec2 &pos, const glm::vec2 &size,
                          std::vector<std::unique_ptr<PlainStaticObject>> &static_objects,
                          std::vector<std::unique_ptr<PlainDynamicObject>> &dynamic_objects);

    static std::vector<std::vector<char>> createTable(const std::filesystem::path &levelPath);

    std::vector<std::vector<std::vector<char>>> stages_{};

    float left_ = 0;
    float right_ = 0;
    float top_ = 0;
    float bottom_ = 0;
};


#endif //DRAW_LEVEL_GENERATOR_H
