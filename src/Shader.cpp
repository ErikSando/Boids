#include <fstream>
#include <cstring>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"

const char* read_file(const char* file_path) {
    std::ifstream file;
    file.open(file_path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << file_path << std::endl;
        return nullptr;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size + 1];

    if (!file.read(buffer, size)) {
        delete[] buffer;
        std::cout << "Failed to read file: " << file_path << std::endl;
        return "";
    }

    buffer[size] = '\0';

    return buffer;
}

Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path) {
    const char* vertex_shader_source = read_file(vertex_shader_path);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "Failed to compile vertex shader\n" << info_log << std::endl;
    }

    const char* fragment_shader_source = read_file(fragment_shader_path);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << "Failed to compile fragment shader\n" << info_log << std::endl;
    }

    ID = glCreateProgram();

    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, info_log);
        std::cout << "Failed to link program\n" << info_log << std::endl;
    }

    delete[] vertex_shader_source;
    delete[] fragment_shader_source;

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::Use() {
    glUseProgram(ID);
}

void Shader::CleanUp() {
    glDeleteProgram(ID);
}

void Shader::SetBool(const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::SetInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}