#include <nanobench.h>

#include <cstddef>
#include <iostream>
#include <vector>

#include "math/random.h"

class generator {
   public:
    static void iterate() { seed = ((seed * 1103515245) + 12345) % (1 << 31); }

    static double randd(double a, double b) {
        double x = double(seed) / (1U << 31) * (b - a);
        iterate();
        return x;
    }

   private:
    static inline size_t seed = 1032;
};

std::vector<double> generate_array(size_t n) {
    std::vector<double> a(n);
    for (size_t i = 0; i < n; i++) {
        a[i] = random::uniform(-1., 3.);
    }
    return a;
}

std::vector<double> generate_array_fast(size_t n) {
    std::vector<double> a(n);
    for (size_t i = 0; i < n; i++) {
        a[i] = generator::randd(-1., 3.);
    }
    return a;
}

int main() {
    ankerl::nanobench::Bench bench;
    bench.warmup(1);
    for (size_t n = 10; n <= static_cast<size_t>(1e6); n *= 10) {
        bench.complexityN(n).run("Generate n random numbers",
                                 [&] { generate_array(n); });
    }
    std::cout << bench.complexityBigO() << "\n";

    bench = ankerl::nanobench::Bench();
    for (size_t n = 10; n <= static_cast<size_t>(1e6); n *= 10) {
        bench.complexityN(n).run("Generate n random numbers",
                                 [&] { generate_array_fast(n); });
    }
    std::cout << bench.complexityBigO() << "\n";
}
