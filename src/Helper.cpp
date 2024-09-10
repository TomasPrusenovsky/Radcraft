#include "Helper.h"

#include <iostream>
#include <ostream>

std::vector<unsigned int> CreateIndices(int count) {
    std::vector<unsigned int> indices;
    indices.resize(count * 36);
    std::array<unsigned int, 36> baseIndices = {
        // Back face
        0, 1, 2, 2, 3, 0,
        // Front face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 13, 14, 14, 15, 12,
        // Bottom face
        16, 17, 18, 18, 19, 16,
        // Top face
        20, 21, 22, 22, 23, 20};

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < baseIndices.size(); j++) {
            unsigned int currentIndice = baseIndices[j] + i * 24;
            indices.emplace_back(currentIndice);
        }
    }

    return indices;

}
