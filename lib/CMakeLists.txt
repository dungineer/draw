add_subdirectory(glfw)
add_subdirectory(glew-cmake)
add_subdirectory(soil)
add_subdirectory(glm)

set(THIRDPARTY_LIBS
        glfw
        libglew_static
        soil
        glm
        PARENT_SCOPE
        )
