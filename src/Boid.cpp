#include <random>

#include "glad/glad.h"

#include "Boid.h"
#include "Math.h"
#include "Program.h"

Boid::Boid() {
    position.x = (float) std::rand() / RAND_MAX * 2.0f - 1.0f;
    position.y = (float) std::rand() / RAND_MAX * 2.0f - 1.0f;
}

Boid::~Boid() {

}

void Boid::UpdateVelocity(const float delta, Vector2& mouse_pos, std::vector<Boid*>* boids) {
    Vector2 window_dimensions(WINDOW_WIDTH, WINDOW_HEIGHT);
    Vector2 target(mouse_pos.x / window_dimensions.x * 2.0 - 1.0, -mouse_pos.y / window_dimensions.y * 2.0 + 1.0);

    std::vector<Boid*> proximal_boids;
    Vector2 avg_pos(0.0f, 0.0f);
    Vector2 avg_prox_pos(0.0f, 0.0f);
    Vector2 closest_position;
    float closest_distance = BOID_RANGE;
    int n_prox_boids = 0;

    //for (int i = 0; i < boids->size(); i++) {
        //Boid* boid = boids->at(i);
    for (Boid* boid : *boids) {
        if (boid == this) continue;

        Vector2 pos = boid->position;
        avg_pos += pos;

        float distance = (position - pos).magnitude();

        if (distance < BOID_RANGE) {
            avg_prox_pos += pos;
            n_prox_boids++;
            proximal_boids.emplace_back(boid);

            if (distance < closest_distance) {
                closest_distance = distance;
                closest_position = pos;
            }
        }
    }

    acceleration = Vector2::Zero();

    // if (n_prox_boids > 0) {
    //     avg_prox_pos /= n_prox_boids;
        
    //     Vector2 offset = avg_prox_pos - position;
    //     float dist_from_avg = offset.magnitude();
        
    //     if (dist_from_avg > BOID_RANGE * COHESION_THRESHOLD) { // cohesion
    //         acceleration += offset.normalised() * delta;
    //     }
    //     else if (closest_distance < BOID_RANGE * ALIGNMENT_THRESHOLD) { // alignment
            
    //     }
    //     else { // seperation
    //         acceleration += -offset.normalised() * delta;
    //     }
    // }

    acceleration += (target - position).normalised() * delta * ACCELERATION_MULTIPLIER;

    velocity += acceleration;

    if (velocity.magnitude() > MAX_SPEED) {
        velocity = velocity.normalised() * MAX_SPEED;
    }
}

void Boid::Update(const float delta) {
    if (velocity.magnitude() == 0) return;

    float dot = Vector2::Dot(velocity, Vector2::Left());
    float cross = Vector2::Cross(velocity, Vector2::Left());
    float cosine = dot / velocity.magnitude();
    float angle = std::acos(cosine);

    if (cross > 0) angle = TwoPI - angle;

    orientation = angle;
    position += velocity * delta;
}

void Boid::Render(unsigned int VAO, unsigned int VBO, unsigned int EBO, Vector2& offset) {
    Vector2 front = position - 0.8 * length * Vector2(std::cos(orientation), std::sin(orientation));
    Vector2 back = position + 0.2 * length * Vector2(std::cos(orientation), std::sin(orientation));

    float t1o = orientation + 0.4;
    float t2o = orientation - 0.4;

    Vector2 tail1 = front + tail_length * Vector2(std::cos(t1o), std::sin(t1o));
    Vector2 tail2 = front + tail_length * Vector2(std::cos(t2o), std::sin(t2o));

    front += offset;
    back += offset;
    tail1 += offset;
    tail2 += offset;

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