#include "math/trapezium.h"
#include "math/vec3.h"
#include <cmath>
#include <iostream>

double f(double x) { return sin(x); }

int main() {
  std::cout << "Hello world !" << std::endl;

  vec3 a(3, 2, 1);
  a.print();

  std::cout << "The integral of sin between 0 and pi is : "
            << integration::trapezium(0, M_PI, f, 1000) << std::endl;

  return 0;
}