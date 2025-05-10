#pragma once

#include <vector>

#include "Boid.h"
#include "Shader.h"

class BoidHandler {
    public:

    BoidHandler(int initial_quantity, Shader* boid_shader);
    ~BoidHandler();

    std::vector<Boid*> boids;
    Shader* shader;

    unsigned int VAO, VBO, EBO;

    void CreateBoids(int quantity = 1);
    void ClearBoids();
    void UpdateBoids(const float delta);
    void RenderBoids();
};