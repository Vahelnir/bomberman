//
// Created by valentin on 21/02/18.
//
#include <glad/glad.h>
#include "shader.hpp"

// Public functions
Shader::Shader(std::string vertex_path, std::string fragment_path) {
    // On récupere nos fichiers
    FILE *vertex = fopen(vertex_path.c_str(), "r");
    FILE *fragment = fopen(fragment_path.c_str(), "r");

    // On vérifie qu'ils existent bien
    if (vertex == nullptr || fragment == nullptr) {
        printf("ERROR::SHADER::FILE::NOT_FOUND");
    }

    // On cherche la taille totale des fichiers
    long vertex_size = 0;
    long fragment_size = 0;

    // On récupere la position du dernier caractère
    fseek(vertex, 0, SEEK_END);
    fseek(fragment, 0, SEEK_END);
    vertex_size = (int) ftell(vertex);
    fragment_size = (int) ftell(fragment);
    rewind(vertex);
    rewind(fragment);

    // On créé nos tableaux de la taille du fichier
    char vertex_source[vertex_size + 1];
    char fragment_source[fragment_size + 1];

    // On lit les fichiers
    fread(vertex_source, vertex_size, 1, vertex);
    fread(fragment_source, fragment_size, 1, fragment);

    vertex_source[vertex_size] = '\0';
    fragment_source[fragment_size] = '\0';

    // On détruit les pointeurs
    fclose(vertex);
    fclose(fragment);

    // On créé les shaders
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    this->compile(vertex_shader, vertex_source);
    this->compile(fragment_shader, fragment_source);

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
