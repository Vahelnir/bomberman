//
// Created by valentin on 23/02/18.
//

#include "tilemap.h"

Tilemap::Tilemap(Shader *shader_program, int width_in_tile, int height_in_tile, int tile_width, int tile_height) {
    // On crée nos VAO, VBO et EBO
    GLuint vao;
    // On créé le vao
    glGenVertexArrays(1, &vao);
    Object::init(vao);

    this->vao = vao;
    this->width_in_tile = width_in_tile;
    this->height_in_tile = height_in_tile;
    this->tile_width = tile_width;
    this->tile_height = tile_height;
    this->shader_program = shader_program;

    this->shader_program->use();

    glUniform1i(glGetUniformLocation(this->shader_program->program_id, "tile_texture"), 0);
}

void Tilemap::add_tile(int x, int y, Object *tile, int type) {
    tile->x = x;
    tile->y = y;
    tile->z = 1;
    tile->type = type;
    this->tiles.push_back(tile);
}

void Tilemap::add_player(int x, int y, Player *player) {
    player->x = x;
    player->y = y;
    player->z = 2;
    player->tilemap = this;
    this->players.push_back(player);
}

void Tilemap::update() {
    for (auto player : this->players) {
        player->update(this);
    }
}

void Tilemap::render(int screen_width, int screen_height, float *view, float *projection) {
    // On utilise le program
    this->shader_program->use();

    glUniformMatrix4fv(glGetUniformLocation(this->shader_program->program_id, "view"), 1, GL_FALSE,
                       view);
    glUniformMatrix4fv(glGetUniformLocation(this->shader_program->program_id, "projection"), 1, GL_FALSE, projection);
    // On bind notre VAO pour l'utiliser
    glBindVertexArray(this->vao);

    for (auto tile : this->tiles) {
        tile->render(screen_width, screen_height, this->shader_program);
    }

    for (auto player : this->players) {
        player->render(screen_width, screen_height, this->shader_program);
    }
}

void Tilemap::destroy() {
    glDeleteVertexArrays(1, &this->vao);
    Object::clean();
}

Object *Tilemap::get_tile_at(int x, int y) {
    for (auto tile : this->tiles) {
        if (tile->x == x && tile->y == y) {
            return tile;
        }
    }
    return nullptr;
}

