#include <nanobench.h>

#include <cmath>
#include <cstddef>
#include <iostream>

#include "math/trapezium.h"

int main() {
    ankerl::nanobench::Bench bench;
    bench.warmup(1);
    for (size_t n = 10; n <= static_cast<size_t>(1e6); n *= 10) {
        bench.complexityN(n).run("Integrate exp(-x) with trapezium", [&] {
            integration::trapezium(0, 1, [](double x) { return exp(-x); }, n);
        });
    }
    std::cout << bench.complexityBigO() << "\n";
}
