//
// Created by valentin on 01/03/18.
//

#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/detail/type_mat4x4.hpp>
#include "camera.h"
#include "tiles/tilemap.h"

class Game {
public:

    int height, width;

    Game(std::string title, int width, int height);

    void init();

    void createWindow();

    void destroy();

    void loop();

    bool isReady();

    int shouldClose();

private:
    GLFWwindow *window;
    std::string title;

    Camera camera;
    Tilemap *tilemap;
    glm::mat4 projection;

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void error_callback(int error, const char *description);

    void process_input(GLFWwindow *window);
};

#endif //BOMBERMAN_GAME_H
