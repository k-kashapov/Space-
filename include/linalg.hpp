#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <array>
#include <cassert>
#include <cmath>

using v2f = sf::Vector2f;
using v3f = sf::Vector3f;

#define EPS 1e-6

template <typename T, size_t N, size_t M> class Matrix {
    std::array<std::array<T, M>, N> data_;

  public:
    Matrix() = default;

    Matrix(const std::initializer_list<std::array<T, M>> &init) {
        auto init_ptr = init.begin();
        for (size_t i = 0; i < init.size(); i++) {
            data_[i] = *init_ptr;

            ++init_ptr;
        }
    }

    std::array<T, M> &operator[](size_t index) {
        assert(index < N);
        return data_[index];
    }

    const std::array<T, M> &operator[](size_t index) const {
        assert(index < N);
        return data_[index];
    }

    sf::Vector3<T> as_vec(size_t i) const {
        assert(i < N);
        return {data_[i][0], data_[i][1], data_[i][2]};
    }

    sf::Vector3<T> x() const {
        return as_vec(0);
    }

    sf::Vector3<T> y() const {
        return as_vec(1);
    }

    sf::Vector3<T> z() const {
        return as_vec(2);
    }

    Matrix<T, M, N> transpose() const {
        Matrix<T, M, N> res;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                res[j][i] = (*this)[i][j];
            }
        }

        return res;
    }
};

using m33 = Matrix<float, 3, 3>;

float dot(const v3f &a, const v3f &b);

float norm2(const v3f &v);

float norm(const v3f &v);

float norm_l1(const v3f &v);

v3f normalized(const v3f &v);

v3f matmul(const v3f &v, const m33 &m);

v3f operator^(v3f a, v3f b);

v3f rotate(const v3f &v, const v3f &axis, float angle);

m33 rotate(const m33 &m, const v3f &axis, float angle);
