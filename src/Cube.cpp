#include "Cube.h"
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

static constexpr float block_size = 1.0f / 16.0f;
static constexpr std::array verticesBase = {
            // Positions          // UV Coordinates

            // Back face (using the grass side texture)
            Vertex{{-0.5f, -0.5f, -0.5f}, {3 * block_size, 1 * block_size}},
            Vertex{{0.5f, -0.5f, -0.5f}, {4 * block_size, 1 * block_size}},
            Vertex{{0.5f, 0.5f, -0.5f}, {4 * block_size, 0 * block_size}},
            Vertex{{-0.5f, 0.5f, -0.5f}, {3 * block_size, 0 * block_size}},

            // Front face (using the grass side texture)
            Vertex{{-0.5f, -0.5f, 0.5f}, {3 * block_size, 1 * block_size}}, // Vertex 4
            Vertex{{0.5f, -0.5f, 0.5f}, {4 * block_size, 1 * block_size}}, // Vertex 5
            Vertex{{0.5f, 0.5f, 0.5f}, {4 * block_size, 0 * block_size}}, // Vertex 6
            Vertex{{-0.5f, 0.5f, 0.5f}, {3 * block_size, 0 * block_size}}, // Vertex 7

            // Left face (using the grass side texture)
            Vertex{{-0.5f, -0.5f, -0.5f}, {4 * block_size, 1 * block_size}}, // Vertex 8
            Vertex{{-0.5f, 0.5f, -0.5f}, {4 * block_size, 0 * block_size}}, // Vertex 9
            Vertex{{-0.5f, 0.5f, 0.5f}, {3 * block_size, 0 * block_size}}, // Vertex 10
            Vertex{{-0.5f, -0.5f, 0.5f}, {3 * block_size, 1 * block_size}}, // Vertex 11

            // Right face (using the grass side texture)
            Vertex{{0.5f, -0.5f, -0.5f}, {3 * block_size, 1 * block_size}}, // Vertex 12
            Vertex{{0.5f, 0.5f, -0.5f}, {3 * block_size, 0 * block_size}}, // Vertex 13
            Vertex{{0.5f, 0.5f, 0.5f}, {4 * block_size, 0 * block_size}}, // Vertex 14
            Vertex{{0.5f, -0.5f, 0.5f}, {4 * block_size, 1 * block_size}}, // Vertex 15

            // Bottom face (using the grass bottom texture)
            Vertex{{-0.5f, -0.5f, -0.5f}, {2 * block_size, 1 * block_size}}, // Vertex 16
            Vertex{{-0.5f, -0.5f, 0.5f}, {2 * block_size, 0 * block_size}}, // Vertex 17
            Vertex{{0.5f, -0.5f, 0.5f}, {3 * block_size, 0 * block_size}}, // Vertex 18
            Vertex{{0.5f, -0.5f, -0.5f}, {3 * block_size, 1 * block_size}}, // Vertex 19

            // Top face (using the grass top texture)
            Vertex{{-0.5f, 0.5f, -0.5f}, {0 * block_size, 0 * block_size}}, // Vertex 20
            Vertex{{-0.5f, 0.5f, 0.5f}, {0 * block_size, 1 * block_size}}, // Vertex 21
            Vertex{{0.5f, 0.5f, 0.5f}, {1 * block_size, 1 * block_size}}, // Vertex 22
            Vertex{{0.5f, 0.5f, -0.5f}, {1 * block_size, 0 * block_size}} // Vertex 23
    };

static constexpr std::array verticesBaseDirt = {
            // Positions          // UV Coordinates

            // Back face (using the grass side texture)
            Vertex{{-0.5f, -0.5f, -0.5f}, {2 * block_size, 1 * block_size}},
            Vertex{{0.5f, -0.5f, -0.5f}, {2 * block_size, 0 * block_size}},
            Vertex{{0.5f, 0.5f, -0.5f}, {3 * block_size, 0 * block_size}},
            Vertex{{-0.5f, 0.5f, -0.5f}, {3 * block_size, 1 * block_size}},

            // Front face (using the grass side texture)
            Vertex{{-0.5f, -0.5f, 0.5f}, {2 * block_size, 1 * block_size}}, // Vertex 4
            Vertex{{0.5f, -0.5f, 0.5f}, {2 * block_size, 0 * block_size}}, // Vertex 5
            Vertex{{0.5f, 0.5f, 0.5f}, {3 * block_size, 0 * block_size}}, // Vertex 6
            Vertex{{-0.5f, 0.5f, 0.5f}, {3 * block_size, 1 * block_size}}, // Vertex 7

            // Left face (using the grass side texture)
            Vertex{{-0.5f, -0.5f, -0.5f}, {2 * block_size, 1 * block_size}}, // Vertex 8
            Vertex{{-0.5f, 0.5f, -0.5f}, {2 * block_size, 0 * block_size}}, // Vertex 9
            Vertex{{-0.5f, 0.5f, 0.5f}, {3 * block_size, 0 * block_size}}, // Vertex 10
            Vertex{{-0.5f, -0.5f, 0.5f}, {3 * block_size, 1 * block_size}}, // Vertex 11

            // Right face (using the grass side texture)
            Vertex{{0.5f, -0.5f, -0.5f}, {2 * block_size, 1 * block_size}}, // Vertex 12
            Vertex{{0.5f, 0.5f, -0.5f}, {2 * block_size, 0 * block_size}}, // Vertex 13
            Vertex{{0.5f, 0.5f, 0.5f}, {3 * block_size, 0 * block_size}}, // Vertex 14
            Vertex{{0.5f, -0.5f, 0.5f}, {3 * block_size, 1 * block_size}}, // Vertex 15

            // Bottom face (using the grass bottom texture)
            Vertex{{-0.5f, -0.5f, -0.5f}, {2 * block_size, 1 * block_size}}, // Vertex 16
            Vertex{{-0.5f, -0.5f, 0.5f}, {2 * block_size, 0 * block_size}}, // Vertex 17
            Vertex{{0.5f, -0.5f, 0.5f}, {3 * block_size, 0 * block_size}}, // Vertex 18
            Vertex{{0.5f, -0.5f, -0.5f}, {3 * block_size, 1 * block_size}}, // Vertex 19

            // Top face (using the grass top texture)
            Vertex{{-0.5f, 0.5f, -0.5f}, {2 * block_size, 1 * block_size}}, // Vertex 20
            Vertex{{-0.5f, 0.5f, 0.5f}, {2 * block_size, 0 * block_size}}, // Vertex 21
            Vertex{{0.5f, 0.5f, 0.5f}, {3 * block_size, 0 * block_size}}, // Vertex 22
            Vertex{{0.5f, 0.5f, -0.5f}, {3 * block_size, 1 * block_size}} // Vertex 23
    };

Cube CreateCube(glm::vec3 positon) {

    Cube result;

    for (int i = 0; i < 24; i++) {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), positon);
        glm::vec3 newPosition = translate * glm::vec4(verticesBase[i].position, 1.0f);
        result.vertices[i] = {newPosition, verticesBase[i].texCoord};
    }

    return result;
}
Cube CreateDirt(glm::vec3 positon) {

    Cube result;

    for (int i = 0; i < 24; i++) {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), positon);
        glm::vec3 newPosition = translate * glm::vec4(verticesBaseDirt[i].position, 1.0f);
        result.vertices[i] = {newPosition, verticesBaseDirt[i].texCoord};
    }

    return result;
}
