#include "math/trapezium.h"

namespace integration {

double trapezium(double a, double b, std::function<double(double)> f,
                 size_t n) {

    double sum = 0.5 * (f(a) + f(b));
    for (size_t i = 1; i < n; i++) {
        double x = a + (b - a) * i / n;
        sum += f(x);
    }

    return sum * (b - a) / n;
}

} // namespace integration
