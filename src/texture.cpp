//
// Created by valentin on 23/02/18.
//

#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_images.h"

Texture::Texture(std::string texture_path, bool is_rgba) {
    GLuint texture;

    stbi_set_flip_vertically_on_load(true);

    int width, height, nr_channels;
    // Chargement de l'image + taille de l'image
    stbi_uc *data = stbi_load(texture_path.c_str(), &width, &height, &nr_channels, 0);
    if (data) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, is_rgba ? GL_RGBA : GL_RGB, width, height, 0, is_rgba ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("ERROR::IMAGE::LOADING");
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    this->height = height;
    this->width = width;
    this->nr_channels = nr_channels;
    this->id = texture;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
