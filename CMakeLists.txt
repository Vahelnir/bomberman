cmake_minimum_required(VERSION 3.9)
project(Bomberman)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(GLM_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(GLAD_DIR "${PROJECT_SOURCE_DIR}/glad")

add_executable(Bomberman src/main.cpp src/shader.cpp src/shader.hpp src/stb_images.h src/texture.cpp src/texture.h src/tiles/tilemap.cpp src/tiles/tilemap.h src/camera.cpp src/camera.h src/game.cpp src/game.h src/player.cpp src/player.h src/object.cpp src/object.h src/direction.h src/direction.h)

#set_target_properties(Bomberman PROPERTIES LINK_FLAGS "-static")

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_library("glad" "glad/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(Bomberman PRIVATE "${GLAD_DIR}/include")

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
target_link_libraries(Bomberman ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} "glad" ${CMAKE_DL_LIBS} m)