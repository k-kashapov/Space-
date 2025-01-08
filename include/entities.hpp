#pragma once

#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

using v2f = sf::Vector2f;
using v3f = sf::Vector3f;
using m33 = std::vector<v3f>;

class Camera;

class SpaceObj {
protected:
    v3f pos = {0, 0, 0};
    m33 basis = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
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
    float mov_spd = 5.0;
    float FOV = 90.0;

public:
    float getSpd() const {
        return mov_spd;
    }

    void Move(const v3f& to) {
        pos += to;
    }

    // Distance to plane
    const float D = 10.0;
    void Draw(sf::RenderWindow& window, const Camera& from) const override {};
};

class Player final : public SpaceShip {
public:
    void Draw(sf::RenderWindow& window, const Camera& from) const override {};
    void Move(const v3f& to) {
        pos += to;
    }
};
