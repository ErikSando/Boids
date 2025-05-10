#pragma once

#include <array>

#include "Vector2.h"

#define TRIANGLES_PER_QUADRANT 6

class Obstacle {
    public:

    Obstacle();
    ~Obstacle();

    float vertices[TRIANGLES_PER_QUADRANT * 12 + 3];
    unsigned int indices[TRIANGLES_PER_QUADRANT * 12];

    Vector2 position;
    float radius = 0.1;

    void CalculateVertices();
    void Render(unsigned int VAO, unsigned int VBO, unsigned int EBO, Vector2& offset);
};