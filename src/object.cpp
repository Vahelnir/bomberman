//
// Created by valentin on 01/03/18.
//

#include "object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Object::Object(Texture *texture) {
    this->texture = texture;
}

GLuint Object::vbo, Object::ebo;

static const float vertices[] = {
        // positions      colors            textures coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};

// On défini l'ordre des points à tracer
static const GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
};

void Object::init(GLuint vao) {
    GLuint vbo, ebo;
    // On créé le VBO
    glGenBuffers(1, &vbo);
    // On créé l'EBO
    glGenBuffers(1, &ebo);
    // On dit qu'on utilise le vao
    glBindVertexArray(vao);

    // On défini le VBO comme un array buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // On lui attribut nos valeurs
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // On défini notre EBO comme un element array buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // On lui attribu nos indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // attribut de position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // attribut de texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    Object::vbo = vbo;
    Object::ebo = ebo;
}

void Object::clean() {
    glDeleteBuffers(1, &Object::vbo);
    glDeleteBuffers(1, &Object::ebo);
}

void Object::render(int screen_width, int screen_height, Shader *shader_program) {
    // On bind notre texture
    this->texture->bind();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3((this->x * this->width) + this->width / 2,
                                            (float) screen_height - this->height / 2 - (this->height * this->y),
                                            this->z));
    model = glm::scale(model, glm::vec3(this->height, this->width, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader_program->program_id, "model"), 1, GL_FALSE,
                       glm::value_ptr(model));

    // On affiche notre element
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}