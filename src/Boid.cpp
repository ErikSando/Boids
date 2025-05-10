#include <random>

#include "glad/glad.h"

#include "Boid.h"
#include "Math.h"

Boid::Boid() {
    position.x = (float) std::rand() / RAND_MAX * 2.0f - 1.0f;
    position.y = (float) std::rand() / RAND_MAX * 2.0f - 1.0f;

    orientation = (float) std::rand() / RAND_MAX * TwoPI;
}

Boid::~Boid() {

}

void Boid::UpdateVelocity(const float delta, std::vector<Boid*>* boids) {
    Vector2 avg_pos(0.0f, 0.0f);

    std::vector<Boid*> proximal_boids;

    //for (int i = 0; i < boids->size(); i++) {
        //Boid* boid = boids->at(i);
    for (Boid* boid : *boids) {
        if (boid == this) continue;

        avg_pos += boid->position;

        if ((position - boid->position).magnitude() < BOID_RANGE) {
            proximal_boids.emplace_back(boid);
        }
    }

    avg_pos /= boids->size() - 1;

    acceleration = (avg_pos - position) * delta;
    velocity += acceleration;

    if (velocity.magnitude() > MAX_SPEED) {
        velocity = velocity.normalised() * MAX_SPEED;
    }
}

void Boid::Update(const float delta) {
    float dot = Vector2::Dot(velocity, Vector2::Left());
    float cross = Vector2::Cross(velocity, Vector2::Left());
    float cosine = dot / velocity.magnitude();
    float angle = std::acos(cosine);

    if (cross > 0) angle = TwoPI - angle;

    orientation = angle;
    position += velocity * delta;
}

void Boid::Render(unsigned int VAO, unsigned int VBO, unsigned int EBO) {
    Vector2 front = position - 0.8 * length * Vector2(std::cos(orientation), std::sin(orientation));
    Vector2 back = position + 0.2 * length * Vector2(std::cos(orientation), std::sin(orientation));

    float t1o = orientation + 0.4;
    float t2o = orientation - 0.4;

    Vector2 tail1 = front + tail_length * Vector2(std::cos(t1o), std::sin(t1o));
    Vector2 tail2 = front + tail_length * Vector2(std::cos(t2o), std::sin(t2o));

    float vertices[] = {
        front.x, front.y, 1.0f,
        tail1.x, tail1.y, 1.0f,
         back.x,  back.y, 1.0f,
        tail2.x, tail2.y, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2
    };

    //glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}