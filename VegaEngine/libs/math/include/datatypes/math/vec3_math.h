#pragma once
#include "math/vec3.h"

template <std::floating_point T>
inline T dot(const vec3<T>& u, const vec3<T>& v) {
    return u.dot(v);
}

template <std::floating_point T>
inline vec3<T> cross(const vec3<T>& u, const vec3<T>& v) {
    return vec3((u.y * v.z) - (u.z * v.y), (u.z * v.x) - (u.x * v.z),
                (u.x * v.y) - (u.y * v.x));
}

template <std::floating_point T>
inline vec3<T> cos(const vec3<T>& u) {
    return vec3<T>(cos(u.x), cos(u.y), cos(u.z));
}

template <std::floating_point T>
inline vec3<T> sin(const vec3<T>& u) {
    return vec3<T>(sin(u.x), sin(u.y), sin(u.z));
}

template <std::floating_point T>
inline vec3<T> tan(const vec3<T>& u) {
    return vec3<T>(tan(u.x), tan(u.y), tan(u.z));
}

template <std::floating_point T>
inline vec3<T> exp(const vec3<T>& u) {
    return vec3<T>(exp(u.x), exp(u.y), exp(u.z));
}