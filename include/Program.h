#pragma once

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "BoidHandler.h"
#include "Input.h"

class Program {
    public:

    Program();
    ~Program();

    void InitWindow(const char* title, int width, int height);
    void InitBoids(int initial_quantity, Shader& boid_shader);

    void Run();
    void Destroy();

    float max_delta = 0.1f;

    private:

    GLFWwindow* window;
    InputHandler* input;
    BoidHandler* boid_handler;

    std::vector<Boid*> boids;

    bool window_setup = false;
    bool boids_setup = false;
    bool running = false;

    void Update(const float delta);
    void Render();

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};