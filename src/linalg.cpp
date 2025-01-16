#include "linalg.hpp"

float dot(const v3f &a, const v3f &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

float norm2(const v3f &v) { return dot(v, v); }

float norm(const v3f &v) { return std::sqrt(norm2(v)); }

float norm_l1(const v3f &v) { return std::abs(v.x) + std::abs(v.y) + std::abs(v.z); }

v3f normalized(const v3f &v) {
    float l = norm(v);
    assert(std::abs(l) > EPS);
    return v / l;
}

v3f matmul(const v3f &v, const m33 &m) {
    m33 trans = m.transpose();
    return {dot(v, trans.x()), dot(v, trans.y()), dot(v, trans.z())};
}

// Cross Product
v3f operator^(v3f a, v3f b) {
    return v3f{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
    };
}

// Rodrigues' rotation formula
v3f rotate(const v3f &v, const v3f &axis, float angle) {
    v3f ax = normalized(axis);
    return v * std::cos(angle) + (ax ^ v) * std::sin(angle) +
           ax * dot(ax, v) * (1 - std::cos(angle));
}

m33 rotate(const m33 &m, const v3f &axis, float angle) {
    m33 res;
    v3f ax = normalized(axis);

    for (size_t i = 0; i < 3; i++) {
        v3f v = m.as_vec(i);
        v3f rotated = v * std::cos(angle) + (ax ^ v) * std::sin(angle) +
                      ax * dot(ax, v) * (1 - std::cos(angle));
        res[i][0] = rotated.x;
        res[i][1] = rotated.y;
        res[i][2] = rotated.z;
    }

    return res;
}
