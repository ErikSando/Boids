#pragma once

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "BoidHandler.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

class Program {
    public:

    Program();
    ~Program();

    void InitWindow(const char* title, int width, int height);
    void InitEntities(int initial_boids, int initial_obstacles, Shader& boid_shader, Shader& obstacle_shader);

    void Run();
    void Destroy();

    float max_delta = 0.1f;

    private:

    GLFWwindow* window;
    BoidHandler* boid_handler;

    bool window_setup = false;
    bool boids_setup = false;
    bool running = false;

    void Update(const float delta);
    void Render();

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void CursorPositionCallback(GLFWwindow* window, double x, double y);
};