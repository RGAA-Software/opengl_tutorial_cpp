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
find_package(assimp REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SHADER_SRCS
        shader/ShaderLoader.h
        shader/ShaderLoader.cpp
        shader/ShaderProgram.h
        )

set(RENDERER_INCS
        renderer/IRenderer.h
        renderer/Sprite.h
        renderer/Director.h
        renderer/MultiBars.h
        renderer/Cube.h
        renderer/model/Vertex.h
        renderer/model/Model.h
        renderer/model/Mesh.h
        renderer/model/Texture.h
        renderer/model/TextureLoader.h
        )

aux_source_directory(renderer RENDERER_SRCS)
aux_source_directory(renderer/model RENDERER_MODEL_SRCS)

add_executable(opengl_tutorial
        main.cpp
        gl_func_adapter.h
        InputProcessor.cpp
        InputProcessor.h
        ${SHADER_SRCS}
        ${RENDERER_SRCS}
        ${RENDERER_INCS}
        ${RENDERER_MODEL_SRCS})

target_link_libraries(opengl_tutorial PRIVATE glfw)
target_link_libraries(opengl_tutorial PRIVATE GLEW::GLEW)
target_link_libraries(opengl_tutorial PRIVATE glm::glm)
target_link_libraries(opengl_tutorial PRIVATE assimp::assimp)