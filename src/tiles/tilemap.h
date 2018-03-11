//
// Created by valentin on 23/02/18.
//

#ifndef BOMBERMAN_TILEMAP_H
#define BOMBERMAN_TILEMAP_H

#include <glm/detail/type_mat4x4.hpp>
#include <vector>
#include "../shader.hpp"
#include "../object.h"
#include "../player.h"

class Tilemap {
public:
    Shader *shader_program;
    int width_in_tile, height_in_tile, tile_width, tile_height;

    std::vector<Object *> tiles;
    std::vector<Player *> players;

    Tilemap(Shader *shader_program, int width_in_tile, int height_in_tile, int tile_width, int tile_height);

    void add_tile(int x, int y, Object *tile, int type);

    void render(int screen_width, int screen_height, float *view, float *projection);

    void update();

    void destroy();

    void add_player(int x, int y, Player *player);

    Object* get_tile_at(int x, int y);

private:
    GLuint vao;

};

#endif //BOMBERMAN_TILEMAP_H
