#pragma once
#include <iostream>

class vec3
{
public:
    double x;
    double y;
    double z;

    vec3(double x, double y, double z) : x(x), y(y), z(z) {};

    void print()
    {
        std::cout << x << " " << y << " " << z << std::endl;
    }
};