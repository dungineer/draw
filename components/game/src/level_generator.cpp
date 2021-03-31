#include <level_generator.h>


void LevelGenerator::loadLevel(const std::filesystem::path &levelPath) {
    stages_.emplace_back(createTable(levelPath));
}

std::vector<std::vector<char>> LevelGenerator::createTable(const std::filesystem::path &levelPath) {
    std::vector<std::vector<char>> table{};

    try {
        std::ifstream file(levelPath);

        std::string line{};
        while (std::getline(file, line)) {
            table.emplace_back();
            for (auto c : line) {
                if (' ' != c) {
                    table.back().emplace_back(c);
                }
            }
        }

    } catch (std::exception &e) {
        std::cout << "ERROR::LEVEL_GENERATOR::FAILED_TO_LOAD::" << levelPath << e.what() << std::endl;
    }

    std::cout << "LEVEL_GENERATOR::STAGE_LOADED::" << levelPath << std::endl;

    return table;
}

void LevelGenerator::getObject(char symbol, const glm::vec2 &pos, const glm::vec2 &size,
                               std::vector<std::unique_ptr<PlainStaticObject>> &static_objects,
                               std::vector<std::unique_ptr<PlainDynamicObject>> &dynamic_objects) {
    switch (symbol) {
        case '#':
            static_objects.emplace_back(std::make_unique<SolidBlock>(pos, size));
        case '1':
            static_objects.emplace_back(std::make_unique<Block>(pos, size, glm::vec4{Colors::Red, 1.0F}));
        case '2':
            static_objects.emplace_back(std::make_unique<Block>(pos, size, glm::vec4{Colors::Green, 1.0F}));
        case '3':
            static_objects.emplace_back(std::make_unique<Block>(pos, size, glm::vec4{Colors::Blue, 1.0F}));
        case '4':
            static_objects.emplace_back(std::make_unique<Block>(pos, size, glm::vec4{Colors::Gold, 1.0F}));
        default:
            static_objects.emplace_back(std::make_unique<Block>(pos, size, glm::vec4{Colors::Black, 1.0F}));
    }
}

std::pair<std::vector<std::unique_ptr<PlainStaticObject>>, std::vector<std::unique_ptr<PlainDynamicObject>>>
LevelGenerator::generateObjects(int stage) {
    std::vector<std::unique_ptr<PlainStaticObject>> static_objects{};
    std::vector<std::unique_ptr<PlainDynamicObject>> dynamic_objects{};

    auto row_count = stages_.at(stage).size();
    auto column_count = stages_.at(stage).front().size();

    auto x_size = (right_ - left_) / column_count;
    auto y_size = (top_ - bottom_) / row_count;

    for (size_t row = 0; row < row_count; ++row) {
        for (size_t column = 0; column < column_count; ++column) {
            auto pos = glm::vec2{x_size / 2.0F + x_size * column, y_size / 2.0F + y_size * row};
            auto size = glm::vec2{x_size, y_size};

            switch (stages_.at(stage)[row][column]) {
                case '#':
                    static_objects.emplace_back(std::make_unique<SolidBlock>(pos, size));
                    break;
                case '1':
                    static_objects.emplace_back(std::make_unique<Block>(pos, size, glm::vec4{Colors::Red, 1.0F}));
                    break;
                case '2':
                    static_objects.emplace_back(std::make_unique<Block>(pos, size, glm::vec4{Colors::Green, 1.0F}));
                    break;
                case '3':
                    static_objects.emplace_back(std::make_unique<Block>(pos, size, glm::vec4{Colors::Blue, 1.0F}));
                    break;
                case '4':
                    static_objects.emplace_back(std::make_unique<Block>(pos, size, glm::vec4{Colors::Gold, 1.0F}));
                    break;
                default:
                    break;
            }
        }
    }

    return {std::move(static_objects), std::move(dynamic_objects)};
}
