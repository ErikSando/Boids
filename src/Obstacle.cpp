#include "glad/glad.h"

#include "Math.h"
#include "Obstacle.h"

Obstacle::Obstacle() {
    position.x = (float) std::rand() / RAND_MAX * - 0.5f;
    position.y = (float) std::rand() / RAND_MAX * - 0.5f;

    radius = 0.1f;

    CalculateVertices();
}

Obstacle::~Obstacle() {

}

void Obstacle::CalculateVertices() {
    vertices[0] = position.x;
    vertices[1] = position.y;
    vertices[2] = 1.0f;

    int v = 1;

    for (int q = 0; q < 4; q++) {
        float angle_0 = q * PI / 2;

        for (int t = 0; t < TRIANGLES_PER_QUADRANT; t++) {
            float increment = PI / 2 / TRIANGLES_PER_QUADRANT;
            float angle = angle_0 + t * increment;

            float vertex_x = position.x + radius * std::cos(angle);
            float vertex_y = position.y + radius * std::sin(angle);

            vertices[v * 3] = vertex_x;
            vertices[v * 3 + 1] = vertex_y;
            vertices[v * 3 + 2] = 1.0f;

            v++;
        }
    }

    for (int i = 0; i < TRIANGLES_PER_QUADRANT * 4; i++) {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = std::max((i + 2) % (TRIANGLES_PER_QUADRANT * 4 + 1), 1);
    }
}

void Obstacle::Render(unsigned int VAO, unsigned int VBO, unsigned int EBO, Vector2& offset) {
    float offset_vertices[TRIANGLES_PER_QUADRANT * 12 + 3];

    unsigned int i[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1
    };

    std::copy(std::begin(vertices), std::end(vertices), offset_vertices);

    for (int i = 0; i < TRIANGLES_PER_QUADRANT * 12 + 3; i += 3) {
        offset_vertices[i] += offset.x;
        offset_vertices[i + 1] += offset.y;
    }

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(offset_vertices), offset_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, TRIANGLES_PER_QUADRANT * 12, GL_UNSIGNED_INT, 0);
}