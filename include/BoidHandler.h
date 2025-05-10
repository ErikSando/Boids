#pragma once

#include <vector>

#include "Boid.h"
#include "Obstacle.h"
#include "Shader.h"

class BoidHandler {
    public:

    BoidHandler(const int initial_boids, const int initial_obstacles, Shader* boid_shader, Shader* obstacle_shader);
    ~BoidHandler();

    std::vector<Boid*> boids;
    std::vector<Obstacle*> obstacles;

    Shader* b_shader;
    Shader* o_shader;

    Vector2 offset;

    unsigned int VAO, VBO, EBO;

    void CreateBoids(int quantity = 1);
    void CreateObstacles(int quantity = 1);
    void Reset();
    void Update(const float delta, Vector2& mouse_pos);
    void Render();
};