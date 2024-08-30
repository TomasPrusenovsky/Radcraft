#include "Framer/Framer.h"
#include <array>

int main() {

  std::array<float, 8> vertices = {
    -1.0f, 1.0f,
    1.0f, 1.0f,
    -1.0f, -1.0f,
    1.0f, -1.0f,
  };

  fr::Window window{800, 800, "Radcraft"};

  fr::Shader shader(RESOURCES_PATH"shaders/shader.vert", RESOURCES_PATH"shaders/shader.frag");
  fr::VBO VBO{vertices.data(), sizeof(vertices) * sizeof(float)};
  fr::VAO VAO{};
  VAO.SpecifyData(0, 2, 0);
  VAO.BindVertexBuffer(VBO, 0, 0, 2 * sizeof(float));

  while (window.IsRunning()) {
    glViewport(0, 0, window.Width(), window.Height());
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Bind();
    VAO.Bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    window.OnUpdate();
  }

  std::cout << "Hello, World!\n";
}