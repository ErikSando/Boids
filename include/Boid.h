#pragma once

#include "Vector2.h"

#define BOID_RANGE 0.1
#define MAX_SPEED 0.2

class Boid {
    public:

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    float orientation = 0.0f;
    float length = 0.03f;
    float tail_length = 1.5f * length;

    Boid();
    ~Boid();

    void UpdateVelocity(const float delta, std::vector<Boid*>* boids);
    void Update(const float delta);
    void Render(unsigned int VAO, unsigned int VBO, unsigned int EBO);
};