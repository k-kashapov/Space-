#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include "linalg.hpp"

class Camera;

class Model_I {
  protected:
    std::vector<v3f> points;

  public:
    Model_I(std::initializer_list<v3f> init) : points(init) {};
    virtual sf::VertexArray ToPrimitives2D(std::vector<v2f> screen_space_pts) const = 0;
    virtual ~Model_I() {};

    size_t size() const { return points.size(); }

    v3f &operator[](size_t idx) { return points[idx]; }

    const v3f &operator[](size_t idx) const { return points[idx]; }
};

struct FullMeshModel : public Model_I {
    FullMeshModel(std::initializer_list<v3f> init) : Model_I(init) {};
    sf::VertexArray ToPrimitives2D(std::vector<v2f> screen_space_pts) const override;
};
