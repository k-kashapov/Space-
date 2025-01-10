#pragma once

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

#include "linalg.hpp"

class Camera;

class SpaceObj {
protected:
    v3f pos = {0, 0, 0};
    m33 basis = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
    };

public:
    v3f getPos() const {
        return pos;
    }

    void setPos(const v3f& to) {
        pos = to;
    }

    m33 getBasis() const {
        return basis;
    }

    void setBasis(const m33& new_b) {
        basis = new_b;
    }

    void Rotate(const v3f& axis, float angle) {
        basis = rotate(basis, axis, angle);
    }

    virtual void Draw(sf::RenderWindow& window, const Camera& from) const = 0;
};

class SpaceShip : public SpaceObj {
    float mov_spd;
    std::vector<v3f> model;

public:
    SpaceShip()
    : mov_spd(5.0),
    model ({
        {-100,    0,    0},
        {   0,  100,    0},
        { 100,    0,    0},
        {   0, -100,    0},
        {   0,    0,  100}
    })
    {}

    float getSpd() const {
        return mov_spd;
    }

    void Draw(sf::RenderWindow& window, const Camera& from) const override;
};

class Camera final : public SpaceObj {
    float mov_spd = 10.0;
    float rot_spd = 0.03;

public:
    float getSpd() const {
        return mov_spd;
    }

    void Move(const v3f& to) {
        pos += to;
    }

    // Distance to plane
    const float D = 50.0;
    void Draw(sf::RenderWindow& window, const Camera& from) const override {};

    void Rotate(const v3f& axis) {
        basis = rotate(basis, axis, rot_spd);
    }
};

class Player final : public SpaceShip {
public:
    void Draw(sf::RenderWindow& window, const Camera& from) const override {};
    void Move(const v3f& to) {
        pos += to;
    }
};
