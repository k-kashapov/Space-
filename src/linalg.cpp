#include "linalg.hpp"

float dot(const v3f& a, const v3f& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float norm2(const v3f& v) {
    return dot(v, v);
}

float norm(const v3f& v) {
    return std::sqrt(norm2(v));
}
