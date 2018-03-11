//
// Created by valentin on 23/02/18.
//

#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 direction, glm::vec3 lookUp) {
    this->pos = pos;
    this->direction = direction;
    this->lookUp = lookUp;
}

void Camera::move_right() {
    this->pos.x += this->speed * this->zoom;
    this->direction.x += this->speed * this->zoom;
}

void Camera::move_left() {
    this->pos.x -= this->speed * this->zoom;
    this->direction.x -= this->speed * this->zoom;
}

void Camera::move_up() {
    this->pos.y += this->speed * this->zoom;
    this->direction.y += this->speed * this->zoom;
}

void Camera::move_down() {
    this->pos.y -= this->speed * this->zoom;
    this->direction.y -= this->speed * this->zoom;
}

glm::mat4 Camera::render() {
    glm::mat4 view = glm::lookAt(
            this->pos, // Camera is at (4,3,3), in World Space
            this->direction, // and looks at the origin
            this->lookUp  // Head is up (set to 0,-1,0 to look upside-down)
    );
    view = glm::scale(view, glm::vec3(this->zoom, this->zoom, 1.0f));
    return view;
}
