cmake_minimum_required(VERSION 3.17)
project(draw)

set(CMAKE_CXX_STANDARD 20)

set(GLEW_PATH C:/lib/glew-2.1.0-win32/glew-2.1.0/lib/Release/Win32/glew32s.lib)
set(GLFW3_PATH C:/lib/glfw-3.3.2.bin.WIN32/lib-vc2019/glfw3.lib)

find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_FOUND:= ${OPENGL_FOUND}")
message(STATUS "OPENGL_LIBRARY:= ${OPENGL_LIBRARY}")
message(STATUS "OPENGL_LIBRARIES:= ${OPENGL_LIBRARIES}")

add_executable(draw main.cpp include/shader.h include/texture.h include/camera.h include/cube.h include/lamp.h)
add_subdirectory(lib/soil)
target_include_directories(draw PUBLIC ${CMAKE_SOURCE_DIR}/include lib/soil/inc)
target_link_libraries(draw ${GLEW_PATH} ${GLFW3_PATH} ${OPENGL_LIBRARIES} soil)
