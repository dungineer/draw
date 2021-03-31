cmake_minimum_required(VERSION 3.17)
project(Draw)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(components)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        ${THIRDPARTY_LIBS}
        ${COMPONENTS}
        )

# Move resources to executeable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")