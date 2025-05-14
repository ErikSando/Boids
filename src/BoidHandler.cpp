#include "glad/glad.h"

#include "BoidHandler.h"

// change this up so that a shader reference is passed as the second argument
BoidHandler::BoidHandler(const int ib, const int io, Shader* boid_shader, Shader* obstacle_shader) {
    CreateBoids(ib);
    CreateObstacles(io);

    b_shader = boid_shader;
    o_shader = obstacle_shader;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

BoidHandler::~BoidHandler() {
    Reset();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void BoidHandler::Reset() {
    for (Boid* boid : boids) {
        delete boid;
    }

    for (Obstacle* obstacle : obstacles) {
        delete obstacle;
    }

    boids.clear();
}

void BoidHandler::CreateBoids(int quantity) {
    for (int i = 0; i < quantity; i++) {
        boids.emplace_back(new Boid);
    }
}

void BoidHandler::CreateObstacles(int quantity) {
    for (int i = 0; i < quantity; i++) {
        obstacles.emplace_back(new Obstacle);
    }
}

void BoidHandler::Update(const float delta, Vector2& mouse_pos) {
    for (Boid* boid : boids) {
        boid->UpdateVelocity(delta, mouse_pos, &boids, &obstacles);
    }

    offset.x = 0;
    offset.y = 0;

    for (Boid* boid : boids) {
        boid->Update(delta);
        //offset -= boid->position;
    }

    //offset /= boids.size();
}

void BoidHandler::Render() {
    glBindVertexArray(VAO);

    o_shader->Use();

    for (Obstacle* obstacle : obstacles) {
        obstacle->Render(VAO, VBO, EBO, offset);
    }

    b_shader->Use();

    for (Boid* boid : boids) {
        boid->Render(VAO, VBO, EBO, offset);
    }
}