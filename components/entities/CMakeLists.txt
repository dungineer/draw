file(GLOB ENTITIES_SOURCES src/*.cpp)

add_library(entities STATIC ${ENTITIES_SOURCES})

target_include_directories(entities PUBLIC inc)

target_link_libraries(entities PUBLIC
        media
        glm
        )