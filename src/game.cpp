//
// Created by valentin on 01/03/18.
//

#include "game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game(std::string title, int height, int width) {
    this->title = title;
    this->width = width;
    this->height = height;
}

void Game::init() {}

void Game::createWindow() {
    glfwSetErrorCallback(this->error_callback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
    if (this->window == nullptr) {
        printf("Failed to create the window :c");
        glfwTerminate();
    }
    glfwSetWindowUserPointer(this->window, this);
    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD :c");
    }
    glfwSetFramebufferSizeCallback(this->window, this->framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
    // Transparence
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    // Désactiver la syncro verticale
    // glfwSwapInterval(0);
}

void Game::loop() {
    std::string path_prefix = "";

    #ifdef _WIN32
    path_prefix = "../";
    #endif

    Shader shader_program(path_prefix + "shaders/vertex.vert", path_prefix + "shaders/fragment.frag");

    Texture ground_texture(path_prefix + "images/ground.jpg");
    Texture wall_texture(path_prefix + "images/wall.jpg");
    Texture breakable_wall_texture(path_prefix + "images/breakable_wall.jpg");
    Texture player_ninegag(path_prefix + "images/knuckle.png", true);

    int map[15 * 15] = {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 2, 2, 3, 3, 3, 3, 2, 3, 2, 3, 3, 2, 2, 1,
            1, 2, 1, 3, 1, 3, 1, 2, 1, 2, 1, 3, 1, 2, 1,
            1, 2, 2, 2, 3, 3, 2, 3, 2, 2, 3, 3, 3, 2, 1,
            1, 3, 1, 2, 1, 3, 1, 2, 1, 2, 1, 3, 1, 2, 1,
            1, 2, 3, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 1,
            1, 2, 1, 3, 1, 3, 1, 2, 1, 2, 1, 2, 1, 3, 1,
            1, 2, 3, 3, 2, 3, 2, 3, 3, 2, 2, 2, 2, 3, 1,
            1, 2, 1, 2, 1, 2, 1, 3, 1, 2, 1, 2, 1, 3, 1,
            1, 3, 3, 3, 2, 3, 2, 3, 2, 3, 3, 3, 2, 3, 1,
            1, 3, 1, 3, 1, 2, 1, 3, 1, 3, 1, 3, 1, 3, 1,
            1, 2, 2, 3, 3, 3, 3, 3, 2, 3, 2, 3, 3, 2, 1,
            1, 3, 1, 2, 1, 2, 1, 2, 1, 3, 1, 3, 1, 2, 1,
            1, 2, 2, 2, 2, 3, 2, 3, 3, 3, 2, 3, 2, 2, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    Player player(&player_ninegag);
    this->tilemap = new Tilemap(&shader_program, 15, 15, 32, 32);

    int i = 0;
    for (i = 0; i < this->tilemap->height_in_tile * this->tilemap->width_in_tile; i++) {
        int tile_type = map[i];
        Texture *tile_texture = &wall_texture;
        if (tile_type == 2) tile_texture = &ground_texture;
        if (tile_type == 3) tile_texture = &breakable_wall_texture;
        this->tilemap->add_tile(i % this->tilemap->width_in_tile, floor(i / this->tilemap->height_in_tile),
                                new Object(tile_texture), tile_type);
    }
    this->tilemap->add_player(1, 1, &player);
    double previousTime = glfwGetTime();
    int fps = 0;

    this->projection = glm::ortho(0.0f, (float) this->width, 0.0f, (float) this->height, 0.0f,
                                  100.0f);

    while (!this->shouldClose()) {
        double currentTime = glfwGetTime();
        fps++;
        if (currentTime - previousTime >= 1.0) {
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0 / double(fps));
            title += " | Camera -> x = " + std::to_string(this->camera.pos.x) + ", y = " +
                     std::to_string(this->camera.pos.y) +
                     " | " + std::to_string(1000 / double(fps)) + " ms/frame";
            glfwSetWindowTitle(this->window, this->title.c_str());
            fps = 0;
            previousTime += 1.0;
        }

        glfwGetWindowSize(this->window, &this->width, &this->height);
        glfwPollEvents();
        this->process_input(this->window);

        this->tilemap->update();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 view = this->camera.render();
        this->tilemap->render(this->width, this->height, glm::value_ptr(view), glm::value_ptr(this->projection));

        glfwSwapBuffers(this->window);
    }

    this->tilemap->destroy();
}

bool Game::isReady() {
    return this->window != nullptr;
}

int Game::shouldClose() {
    return glfwWindowShouldClose(this->window);
}

void Game::destroy() {
    glfwTerminate();
}


void Game::error_callback(int error, const char *err_str) {
    printf("GLFW Error: %s", err_str);
}

void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    auto *game = static_cast<Game *>(glfwGetWindowUserPointer(window));
    game->width = width;
    game->height = height;
    game->projection = glm::ortho(0.0f, (float) game->width, 0.0f, (float) game->height, 0.0f,
                                  100.0f);
    glViewport(0, 0, width, height);
}

void Game::process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        this->camera.move_up();
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        this->camera.move_down();
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        this->camera.move_left();
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        this->camera.move_right();
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        this->camera.zoom += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        this->camera.zoom -= 0.01f;
    }


    Direction direction = Direction::NONE;
    Player *player = this->tilemap->players.front();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        direction = Direction::UP;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        direction = Direction::DOWN;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        direction = Direction::LEFT;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        direction = Direction::RIGHT;
    }
    if (direction != Direction::NONE)
        player->move(direction);
}