#pragma once

#include <vector>

#include "Obstacle.h"
#include "Vector2.h"

#define BOID_RANGE 0.4
#define ARRIVAL_RADIUS 0.3
#define SEEK_STRENGTH 0.5
#define ORBIT_RADIUS 0.15
#define FLEE_RADIUS 0.4
#define FLEE_STRENGTH 0.3
#define FLEE_LOOK_AHEAD 0.15
#define SEPERATION_RADIUS 0.2
#define MAX_SPEED 0.4
#define MAX_STEER 0.04
#define SEPERATION_STRENGTH 0.0015
#define ALIGNMENT_STRENGTH 0.001
#define COHESION_STRENGTH 0.001

class Boid {
    public:

    Vector2 position;
    Vector2 velocity;
    Vector2 steer;

    float orientation = 0.0f;
    float length = 0.03f;
    float tail_length = 1.5f * length;

    Boid();
    ~Boid();

    void UpdateVelocity(const float delta, Vector2& mouse_pos, std::vector<Boid*>* boids, std::vector<Obstacle*>* obstacles);
    void Update(const float delta);
    void Render(unsigned int VAO, unsigned int VBO, unsigned int EBO, Vector2& offset);
};