#pragma once
#include <functional>

namespace integration {

double trapezium(double a, double b, const std::function<double(double)>& f,
                 size_t n);

}
