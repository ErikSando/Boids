#include <algorithm>

#include "glad/glad.h"

#include "Boid.h"
#include "Math.h"
#include "Program.h"

Boid::Boid() {
    position.x = (float) std::rand() / RAND_MAX * 1.8f - 0.9f;
    position.y = (float) std::rand() / RAND_MAX * 1.8f - 0.9f;
}

Boid::~Boid() {

}

void Boid::UpdateVelocity(const float delta, Vector2& mouse_pos, std::vector<Boid*>* boids, std::vector<Obstacle*>* obstacles) {
    Vector2 window_dimensions(WINDOW_WIDTH, WINDOW_HEIGHT);
    Vector2 goal = (mouse_pos / window_dimensions * 2 - Vector2::One()) * Vector2(1.0f, -1.0f);

    std::vector<Boid*> proximal_boids;
    Vector2 avg_pos;
    Vector2 avg_neighbour_pos;
    Vector2 avg_neighbour_vel;
    int n_neighbours = 0;

    for (Boid* boid : *boids) {
        if (boid == this) continue;

        Vector2 pos = boid->position;
        avg_pos += pos;

        float distance = (position - pos).magnitude();

        if (distance < BOID_RANGE) {
            avg_neighbour_pos += pos;
            avg_neighbour_pos += boid->velocity;
            n_neighbours++;
            proximal_boids.emplace_back(boid);
        }
    }

    steer = Vector2::Zero();

    Vector2 seek;
    Vector2 flee;
    Vector2 seperation;
    Vector2 alignment;
    Vector2 cohesion;

    if (n_neighbours > 0) {
        avg_neighbour_pos /= n_neighbours;
        avg_neighbour_vel /= n_neighbours;

        for (Boid* boid : proximal_boids) {
            Vector2 other_pos = boid->position;
            Vector2 direction = (position - other_pos);
            float distance = direction.magnitude();

            if (distance < SEPERATION_RADIUS && distance > 0) {
                seperation += direction.normalised() / distance;
            }
        }

        seperation *= SEPERATION_STRENGTH;

        alignment = (avg_neighbour_vel - velocity) * ALIGNMENT_STRENGTH;
        cohesion = (avg_neighbour_pos - position) * COHESION_STRENGTH;
    }

    Vector2 seek_direction = (goal - position);
    float seek_distance = seek_direction.magnitude();

    if (seek_distance > 0) {
        seek_direction.normalise();

        if (seek_distance < ARRIVAL_RADIUS) {
            seek_direction *= seek_distance / ARRIVAL_RADIUS;
        }

        seek = (seek_direction * MAX_SPEED - velocity) * SEEK_STRENGTH;
    }

    int n_obstacles = 0;

    if (velocity.magnitude() != 0) {
        for (Obstacle* obstacle : *obstacles) {
            n_obstacles++;

            Vector2 obstacle_pos = obstacle->position;
            Vector2 next_pos = position + velocity.normalised() * FLEE_LOOK_AHEAD;
            Vector2 direction = (next_pos - obstacle_pos);
            float distance = direction.magnitude() - obstacle->radius;
    
            flee += direction.normalised() * MAX_SPEED * (obstacle->radius + 0.1f / distance) - velocity;
        }
    }

    flee *= FLEE_STRENGTH;
    if (n_obstacles != 0) flee /= n_obstacles;

    steer += (seek + flee + seperation + alignment + cohesion) * delta;

    if (steer.magnitude() > MAX_STEER) {
        steer = steer.normalised() * MAX_STEER;
    }
}

void Boid::Update(const float delta) {
    velocity += steer;
    float speed = velocity.magnitude();

    if (speed > MAX_SPEED) {
        velocity = velocity.normalised() * MAX_SPEED;
    }

    if (speed == 0) return;

    float dot = Vector2::Dot(velocity, Vector2::Left());
    float cross = Vector2::Cross(velocity, Vector2::Left());
    float cosine = std::clamp(dot / speed, -1.0f, 1.0f);
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

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}