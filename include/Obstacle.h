#pragma once

#include <array>

#include "Vector2.h"

#define TRIANGLES_PER_QUADRANT 6
#define NUM_VERTICES (TRIANGLES_PER_QUADRANT * 12 + 3)
#define NUM_INDICES (TRIANGLES_PER_QUADRANT * 12)

class Obstacle {
    public:

    Obstacle();
    ~Obstacle();

    float vertices[NUM_VERTICES];
    unsigned int indices[NUM_INDICES];

    Vector2 position;
    float radius = 0.1f;

    void CalculateVertices();
    void Render(unsigned int VAO, unsigned int VBO, unsigned int EBO, Vector2& offset);
};