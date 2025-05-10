#pragma once

#include "Vector2.h"

class Boid {
    public:

    Vector2 position;
    Vector2 velocity;
    
    float orientation;

    Boid();
    ~Boid();

    void Update(const float delta);
    void Render();
};