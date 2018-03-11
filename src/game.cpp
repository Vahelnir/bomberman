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
    // On défini un callback pour les eventuelles erreurs
    glfwSetErrorCallback(this->error_callback);
    // On initialise glfw
    glfwInit();
    // ON défini la version d'opengl à utiliser
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // On défini le profil à charger
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // On créé la fenetre
    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
    // S'il y a une erreur, on l'affiche et on stop le processus
    if (this->window == nullptr) {
        printf("Failed to create the window :c");
        glfwTerminate();
    }
    // On défini le pointeur à la classe active (pour acceder à cette classe dans les callbacks)
    glfwSetWindowUserPointer(this->window, this);
    // On défini la fenetre comme celle actuelle
    glfwMakeContextCurrent(this->window);

    // On initialise Glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD :c");
    }
    // On défini un callback pour le resize de la fenetre
    glfwSetFramebufferSizeCallback(this->window, this->framebuffer_size_callback);
    // On active les tests de profondeur
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

    // Map qui est pour le moment hardcodée
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

    // On crée le joueur
    Player player(&player_ninegag);
    // On crée la map
    this->tilemap = new Tilemap(&shader_program, 15, 15, 32, 32);

    int i = 0;
    // On charge chaque tile et on l'ajoute à la map
    for (i = 0; i < this->tilemap->height_in_tile * this->tilemap->width_in_tile; i++) {
        int tile_type = map[i];
        Texture *tile_texture = &wall_texture;
        if (tile_type == 2) tile_texture = &ground_texture;
        if (tile_type == 3) tile_texture = &breakable_wall_texture;
        this->tilemap->add_tile(i % this->tilemap->width_in_tile, floor(i / this->tilemap->height_in_tile),
                                new Object(tile_texture), tile_type);
    }
    // On ajoute le player à la map à la position 1, 1
    this->tilemap->add_player(1, 1, &player);
    // On crée notre projection orthogonale (car on est un jeu en 2D)
    this->projection = glm::ortho(0.0f, (float) this->width, 0.0f, (float) this->height, 0.0f,
                                  100.0f);

    double previousTime = glfwGetTime();
    int fps = 0;

    while (!this->shouldClose()) {
        double currentTime = glfwGetTime();
        fps++;
        if (currentTime - previousTime >= 1.0) {
            printf("%f ms/frame\n", 1000.0 / double(fps));
            title += " | Camera -> x = " + std::to_string(this->camera.pos.x) + ", y = " +
                     std::to_string(this->camera.pos.y) +
                     " | " + std::to_string(1000 / double(fps)) + " ms/frame";
            glfwSetWindowTitle(this->window, this->title.c_str());
            fps = 0;
            previousTime += 1.0;
        }
        // On récupere la taille de la fenetre
        glfwGetWindowSize(this->window, &this->width, &this->height);
        // On récupere les events
        glfwPollEvents();
        // Et on process les inputs de l'utilisateur (pour le moment)
        this->process_input(this->window);

        // On update la tilemap et tout son contenu
        this->tilemap->update();

        // On reset l'affichage
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // On render la caméra
        glm::mat4 view = this->camera.render();
        // On render la carte
        this->tilemap->render(this->width, this->height, glm::value_ptr(view), glm::value_ptr(this->projection));

        glfwSwapBuffers(this->window);
    }

    // On détruit la map et les objets dedans
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