#ifndef DRAW_COLORS_H
#define DRAW_COLORS_H


#include <glm/glm.hpp>


namespace Colors {
    constexpr auto NoColor = glm::vec4{1.0F, 1.0F, 1.0F, 1.0F};

    constexpr auto White = glm::vec3{1.0F, 1.0F, 1.0F};
    constexpr auto Black = glm::vec3{0.0F, 0.0F, 0.0F};

    constexpr auto Red   = glm::vec3{1.0F, 0.0F, 0.0F};
    constexpr auto Blue  = glm::vec3{0.0F, 1.0F, 0.0F};
    constexpr auto Green = glm::vec3{0.0F, 0.0F, 1.0F};

    constexpr auto Gold   = glm::vec3{1.0F, 0.843F, 0.0F};
    constexpr auto Silver = glm::vec3{0.753F, 0.753F, 0.753F};
}


#endif //DRAW_COLORS_H
