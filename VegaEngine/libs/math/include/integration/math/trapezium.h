#pragma once
#include <functional>

namespace integration {

double trapezium(double a, double b, std::function<double(double)> f, size_t n);

}
