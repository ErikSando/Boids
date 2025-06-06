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
    glfwSetFramebufferSizeCallback(window, Program::FramebufferSizeCallback);
    glfwSetCursorPosCallback(window, Program::CursorPositionCallback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialise GLAD" << std::endl;
        return;
    }

    // disable V-Sync
    //glfwSwapInterval(0);

    glViewport(0, 0, width, height);

    window_setup = true;
}

void Program::InitEntities(int initial_boids, int initial_obstacles, Shader& boid_shader, Shader& obstacle_shader) {
    if (boids_setup) {
        std::cout << "Boids already initialised" << std::endl;
        return;
    }

    boid_handler = new BoidHandler(initial_boids, initial_obstacles, &boid_shader, &obstacle_shader);
    boids_setup = true;
}

void Program::Destroy() {
    running = false;

    if (boids_setup) delete boid_handler;

    if (window_setup) {
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
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    Vector2 mouse_pos(mouseX, mouseY);

    boid_handler->Update(delta, mouse_pos);
}

void Program::Render() {
    glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    boid_handler->Render();
}

void Program::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    int viewport_info[4];
    glGetIntegerv(GL_VIEWPORT, viewport_info);

    glViewport(viewport_info[0], viewport_info[1], width, height);
}

void Program::CursorPositionCallback(GLFWwindow* window, double x, double y) {
    //mouse_pos.x = x;
    //mouse_pos.y = y;
}