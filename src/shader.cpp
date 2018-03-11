//
// Created by valentin on 21/02/18.
//
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include "shader.hpp"

// Public functions
Shader::Shader(std::string vertex_path, std::string fragment_path) {
    std::string vertex_source;
    std::string fragment_source;
    try
    {
        // Open files
        std::ifstream vertex_shader_file(vertex_path);
        std::ifstream fragment_shader_file(fragment_path);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertex_shader_file.rdbuf();
        fShaderStream << fragment_shader_file.rdbuf();
        // close file handlers
        vertex_shader_file.close();
        fragment_shader_file.close();
        // Convert stream into string
        vertex_source = vShaderStream.str();
        fragment_source = fShaderStream.str();
    }
    catch (std::exception e)
    {
        printf("ERROR::SHADER: Failed to read shader files");
    }

    // On créé les shaders
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    this->compile(vertex_shader, vertex_source.c_str());
    this->compile(fragment_shader, fragment_source.c_str());

    // On créé le shader program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader);
    glAttachShader(program_id, fragment_shader);
    glLinkProgram(program_id);

    // On vérifie le status
    int success = 0;
    GLchar infoLog[512];
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program_id, 512, nullptr, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED : %s\n", infoLog);
    }

    // On supprime les shader car on en a plus besoin
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    this->program_id = program_id;
}

void Shader::use() {
    glUseProgram(this->program_id);
}

void Shader::compile(GLuint shader, GLchar const *source) {
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    this->check_compile_errors(shader);
}

void Shader::check_compile_errors(GLuint shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED: %s\n", infoLog);
    }
}
