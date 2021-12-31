#include <iostream>
#include "Vector3.h"

int main() {
  // Image
  const int image_width = 256;
  const int image_height = 256;
  Vector3 x = Vector3(1, 2, 3);
  // Render
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  std::cout << x.getX() << x.getY() << x.getZ();
  std::cerr << "\nDone.\n";
}