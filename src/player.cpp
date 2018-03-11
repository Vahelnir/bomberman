//
// Created by valentin on 01/03/18.
//

#include "player.h"
#include "tiles/tilemap.h"

Player::Player(Texture *texture) : Object(texture) {}

bool Player::collide(int x, int y) {
    if (tilemap->get_tile_at(x, y) != nullptr) {
        return tilemap->get_tile_at(x, y)->type != 2;
    }
    return false;
}

void Player::move_right(int x) {
    if (!this->collide(this->x + x, y))
        this->x += x;
}

void Player::move_left(int x) {
    if (!this->collide(this->x - x, y))
        this->x -= x;
}

void Player::move_down(int y) {
    if (!this->collide(x, this->y + y))
        this->y += y;
}

void Player::move_up(int y) {
    if (!this->collide(x, this->y - y))
        this->y -= y;
}

void Player::move(Direction direction) {
    if (this->can_move) {
        switch (direction) {
            case Direction::UP:
                this->move_up(this->speed);
                break;
            case Direction::DOWN:
                this->move_down(this->speed);
                break;
            case Direction::LEFT:
                this->move_left(this->speed);
                break;
            case Direction::RIGHT:
                this->move_right(this->speed);
                break;
        }
        this->can_move = false;
    }
}

void Player::update(Tilemap *map) {
    this->ticks_since_last_move++;
    if (this->ticks_since_last_move == 20) {
        this->ticks_since_last_move = 0;
        this->can_move = true;
    }
}
