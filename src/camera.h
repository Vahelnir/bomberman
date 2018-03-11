//
// Created by valentin on 23/02/18.
//

#ifndef BOMBERMAN_CAMERA_H
#define BOMBERMAN_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>

class Camera {
public:
    glm::vec3 pos;
    glm::vec3 direction;
    glm::vec3 lookUp;
    float zoom = 1.0f;
    float speed = 2.0f;

    explicit Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 99.0f), glm::vec3 direction = glm::vec3(0.0f),
                    glm::vec3 lookUp = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 render();

    void move_right();

    void move_left();

    void move_up();

    void move_down();
};

#endif //BOMBERMAN_CAMERA_H
