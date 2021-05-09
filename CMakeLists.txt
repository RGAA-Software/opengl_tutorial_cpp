cmake_minimum_required(VERSION 3.16)

SET(CMAKE_TOOLCHAIN_FILE C:/source/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

project(opengl_tutorial)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#如果find 失败，删除cmake-build-debug，重新reload cmake
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SHADER_SRCS
        shader/ShaderLoader.h
        shader/ShaderLoader.cpp
        shader/ShaderProgram.h
        )

add_executable(opengl_tutorial main.cpp gl_func_adapter.h
        ${SHADER_SRCS})

target_link_libraries(opengl_tutorial PRIVATE glfw)
target_link_libraries(opengl_tutorial PRIVATE GLEW::GLEW)
target_link_libraries(opengl_tutorial PRIVATE glm::glm)