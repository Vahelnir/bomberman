//
// Created by valentin on 01/03/18.
//

#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "direction.h"
#include "object.h"
class Tilemap;

class Player : public Object {
public:

    bool can_move = false;
    int ticks_since_last_move = 0;
    int speed = 1;
    Tilemap *tilemap;

    Player(Texture *texture);

    void move(Direction direction);

    void move_down(int y);

    void move_up(int y);

    void move_left(int x);

    void move_right(int x);

    void update(Tilemap *map);

    bool collide(int x, int y);
};

#endif //BOMBERMAN_PLAYER_H
