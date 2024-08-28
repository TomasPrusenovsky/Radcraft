#include "Framer/Framer.h"

int main() {
  fr::Window window{800, 800, "Radcraft"};

  while (window.IsRunning()) {
    window.OnUpdate();
  }

  std::cout << "Hello, World!\n";
}