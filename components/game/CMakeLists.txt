file(GLOB GAME_SOURCES src/*.cpp)

add_library(game STATIC ${GAME_SOURCES})

target_include_directories(game PUBLIC inc)

target_link_libraries(game PUBLIC
        entities
        media
        )