#pragma once

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Boid.h"
#include "Input.h"

class Program {
    public:

    Program(const char* title, int width, int height);
    ~Program();

    void Run();
    void Destroy();

    unsigned int frame_rate = 60;
    float max_delta = 0.1f;

    private:

    GLFWwindow* window;
    InputHandler* input;

    std::vector<Boid*> boids;

    bool setup = false;
    bool running = false;

    void Update(const float delta);
    void Render();

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};