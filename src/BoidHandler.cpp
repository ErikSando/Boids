#include "glad/glad.h"

#include "BoidHandler.h"

// change this up so that a shader reference is passed as the second argument
BoidHandler::BoidHandler(const int initial_quantity, Shader* boid_shader) {
    CreateBoids(initial_quantity);
    shader = boid_shader;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // glBindVertexArray(VAO);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    // glEnableVertexAttribArray(0);
}

BoidHandler::~BoidHandler() {
    ClearBoids();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void BoidHandler::ClearBoids() {
    for (Boid* boid : boids) {
        delete boid;
    }

    boids.clear();
}

void BoidHandler::CreateBoids(int quantity) {
    for (int i = 0; i < quantity; i++) {
        boids.emplace_back(new Boid);
    }
}

void BoidHandler::UpdateBoids(const float delta, Vector2& mouse_pos) {
    for (Boid* boid : boids) {
        boid->UpdateVelocity(delta, mouse_pos, &boids);
    }

    offset.x = 0;
    offset.y = 0;

    for (Boid* boid : boids) {
        boid->Update(delta);
        //offset -= boid->position;
    }

    offset /= boids.size();
}

void BoidHandler::RenderBoids() {
    glBindVertexArray(VAO);

    shader->Use();

    for (Boid* boid : boids) {
        boid->Render(VAO, VBO, EBO, offset);
    }
}