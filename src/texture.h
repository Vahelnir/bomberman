//
// Created by valentin on 23/02/18.
//

#ifndef BOMBERMAN_TEXTURE_H
#define BOMBERMAN_TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture {
public:
    GLuint id;
    int width, height, nr_channels;

    Texture(std::string texture_path, bool is_rgba = false);
    void bind();
};

#endif //BOMBERMAN_TEXTURE_H
