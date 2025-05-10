//#include <ctime>
#include <iostream>
#include <random>

#include "Program.h"
#include "Shader.h"

int main() {
    srand(time(nullptr));

    Program program;
    program.InitWindow("2D Boid Simulation", WINDOW_WIDTH, WINDOW_HEIGHT);

    Shader boid_shader("assets/shaders/boid_vertex_shader.glsl", "assets/shaders/boid_fragment_shader.glsl");

    program.InitBoids(10, boid_shader);
    program.Run();

    return 0;
}