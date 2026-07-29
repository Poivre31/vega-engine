#pragma once
#include <functional>

namespace integration {

/**
 * @brief Integrates function @param f on the interval [ @param a, @param b ]
 * using trapezium method
 *
 * @param n number of function samples
 * @return Integration result
 */
[[nodiscard]] double trapezium(double a, double b,
                               const std::function<double(double)>& f,
                               size_t n);

}  // namespace integration
