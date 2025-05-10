#include <chrono>
#include <iostream>

#include "Program.h"
#include "Time.h"

Program::Program() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialise GLFW" << std::endl;
        return;
    }
}

Program::~Program() {
    Destroy();
}

void Program::InitWindow(const char* title, int width, int height) {
    if (window_setup) {
        std::cout << "Window already created" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialise GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, width, height);
    
    input = new InputHandler(window);

    window_setup = true;
}

void Program::InitBoids(int initial_quantity, Shader& boid_shader) {
    if (boids_setup) {
        std::cout << "Boids already initialised" << std::endl;
        return;
    }

    boid_handler = new BoidHandler(initial_quantity, &boid_shader);
    boids_setup = true;
}

void Program::Destroy() {
    running = false;

    if (boids_setup) delete boid_handler;

    if (window_setup) {
        delete input;

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void Program::Run() {
    if (!window_setup || !boids_setup) {
        return;
    }

    running = true;

    timestamp last_update = Time::Now();
    timestamp last_fps_output = last_update;

    const float fps_output_interval = 1.0f;
    const float frame_multiplier = 1.0f / fps_output_interval;

    int frames = 0;

    // wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (running) {
        if (glfwWindowShouldClose(window)) {
            running = false;
            //Destroy();
            break;
        }

        timestamp now = Time::Now();
        float delta = Time::Difference(now, last_update);
        last_update = now;

        if (delta > max_delta) {
            std::cout << "Delta time too high, skipping frame" << std::endl;
            continue;
        }

        Update(delta);
        Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        frames++;

        timestamp new_now = Time::Now();
        float time_since_fps_output = Time::Difference(new_now, last_fps_output);

        if (time_since_fps_output > fps_output_interval) {
            std::cout << "FPS: " << (int) (frames * frame_multiplier) << std::endl;
            frames = 0;
            last_fps_output += Time::Seconds(fps_output_interval);
        }
    }
}

void Program::Update(const float delta) {
    boid_handler->UpdateBoids(delta);
}

void Program::Render() {
    glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    boid_handler->RenderBoids();
}

void Program::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}