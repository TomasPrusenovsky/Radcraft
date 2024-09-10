#pragma once
#include <Framer/Framer.h>
#include <array>

struct Vertex {
  glm::vec3 position;
  glm::vec2 texCoord;
};

struct Cube {
  std::array<Vertex, 24> vertices;
};

Cube CreateCube(glm::vec3 positon);
Cube CreateDirt(glm::vec3 positon);
