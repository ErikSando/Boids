#include <iostream>
#include <random>

#include "Program.h"
#include "Shader.h"

int main() {
    srand(time(nullptr));

    Program program;
    program.InitWindow("2D Boid Simulation", WINDOW_WIDTH, WINDOW_HEIGHT);

    Shader boid_shader("assets/shaders/boid_vs.glsl", "assets/shaders/boid_fs.glsl");
    Shader obstacle_shader("assets/shaders/obstacle_vs.glsl", "assets/shaders/obstacle_fs.glsl");

    program.InitEntities(20, 1, boid_shader, obstacle_shader);
    program.Run();

    return 0;
}