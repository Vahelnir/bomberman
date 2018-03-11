//
// Created by valentin on 21/02/18.
//

#ifndef BOMBERMAN_SHADER_H
#define BOMBERMAN_SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
public:
    GLuint program_id;

    Shader(std::string vertex_path, std::string fragment_path);

    void use();

private:
    void compile(GLuint shader, GLchar const *source);

    void check_compile_errors(GLuint shader);

};

#endif //BOMBERMAN_SHADER_H
