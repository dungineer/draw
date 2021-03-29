file(GLOB MEDIA_SOURCES src/*.cpp)

add_library(media STATIC ${MEDIA_SOURCES})

target_include_directories(media PUBLIC inc)

target_link_libraries(media PUBLIC
        libglew_static
        soil
        glm
        )