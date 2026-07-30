#include "math/integration/trapezium.h"

namespace integration {

double trapezium(const double a, const double b,
                 const std::function<double(double)>& f, const size_t n) {
    if (n == 0) {
        return 0;
    }
    double sum = 0.5 * (f(a) + f(b));
    double dx = (b - a) / static_cast<double>(n);
    for (size_t i = 1; i < n; i++) {
        double x = a + (static_cast<double>(i) * dx);
        sum += f(x);
    }

    return sum * dx;
}

}  // namespace integration
