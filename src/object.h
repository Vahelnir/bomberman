//
// Created by valentin on 01/03/18.
//

#ifndef BOMBERMAN_OBJECT_H
#define BOMBERMAN_OBJECT_H

#include "texture.h"
#include "shader.hpp"

class Object {
public:
    Texture *texture;
    int x = 0, y = 0, z = 1, width = 32, height = 32, type = 0;

    Object(Texture *texture);

    void render(int screen_width, int screen_height, Shader *shader_program);

    static void init(GLuint vao);

    static void clean();

private:
    static GLuint vbo, ebo;
};

#endif //BOMBERMAN_OBJECT_H
