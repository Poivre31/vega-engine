#include "math/trapezium.h"

namespace integration {

double trapezium(double a, double b, const std::function<double(double)>& f,
                 size_t n) {
    double sum = 0.5 * (f(a) + f(b));
    double dx = (b - a) / static_cast<double>(n);
    for (size_t i = 1; i < n; i++) {
        double x = a + static_cast<double>(i) * dx;
        sum += f(x);
    }

    return sum * dx;
}

}  // namespace integration
