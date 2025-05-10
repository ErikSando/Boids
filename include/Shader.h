#pragma once

#include <iostream>

class Shader {
    public:

    unsigned int vertex_shader;
    unsigned int fragment_shader;
    unsigned int ID;

    Shader(const char* vertex_shader_path, const char* fragment_shader_path);

    void Use();
    void Clean();

    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
};