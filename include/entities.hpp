#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <algorithm>

#include "linalg.hpp"
#include "models.hpp"

class Camera;

class SpaceObj {
  protected:
    v3f pos = {0, 0, 0};
    m33 basis = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
    };

    float mov_spd = 10.0;
    float rot_spd = 0.03;

  public:
    std::string name_ = "";

    SpaceObj(std::string name, v3f position) : name_(name), pos(position) {};

    v3f GetPos() const { return pos; }
    void SetPos(const v3f &to) { pos = to; }

    m33 GetBasis() const { return basis; }
    void SetBasis(const m33 &new_b) { basis = new_b; }

    float GetSpd() const { return mov_spd; }
    void SetSpd(float spd) { mov_spd = spd; }

    float GetRotSpd() const { return rot_spd; }
    void SetRotSpd(float spd) { rot_spd = spd; }

    void Rotate(const v3f &axis, float angle) { basis = rotate(basis, axis, angle); }
    virtual void Draw(sf::RenderWindow &window, const Camera &from) const = 0;
    virtual void Update(float delta) = 0;
    virtual ~SpaceObj() {};
};

static const std::initializer_list<v3f> DefaultShipModel = {
    {-100, 0, 0}, {0, 100, 0}, {100, 0, 0}, {0, -100, 0}, {0, 0, 100}};

class SpaceShip : public SpaceObj {
    float mov_spd;
    FullMeshModel model;

  public:
    SpaceShip(std::string name, v3f position)
        : SpaceObj(name, position), mov_spd(5.0), model(DefaultShipModel) {}

    float getSpd() const { return mov_spd; }

    void Draw(sf::RenderWindow &window, const Camera &from) const override;
    void Update(float delta) override {};
};

class Camera final : public SpaceObj {
    const SpaceObj *target = nullptr;

    const float follow_dist = 150.0;
    const float follow_speed = 1e-4;

    // Distance to plane
    float D = 50.0;

    void rotateToMatch(v3f a, v3f b) {
        v3f diff = normalized(a) - normalized(b);
        float l = norm(diff);

        if (l > 1e-5) {
            Rotate(-a * b, rot_spd * l);
        }
    }

  public:
    Camera(std::string name, v3f position) : SpaceObj(name, position) {}

    void Follow(const SpaceObj *obj) { target = obj; }

    float GetD() const { return D; }
    void SetD(float newD) { D = std::clamp(newD, 10.0f, 100.0f); }

    void Move(const v3f &to) { pos += to; }

    void Draw(sf::RenderWindow &window, const Camera &from) const override {};

    void Update(float delta) override {
        m33 tgt_basis = target->GetBasis();
        v3f tgt_Oy = tgt_basis.as_vec(1);
        v3f tgt_Oz = tgt_basis.as_vec(2);

        v3f tgt_point = target->GetPos() - follow_dist * (tgt_Oy + tgt_Oz);

        v3f diff = tgt_point - pos;
        float l = norm(diff);
        Move(diff * l * follow_speed);

        v3f my_Oy = basis.as_vec(1);
        v3f my_Oz = basis.as_vec(2);

        rotateToMatch(tgt_Oz, my_Oz);
        rotateToMatch(tgt_Oy, my_Oy);
    };
};

class Player final : public SpaceShip {
  public:
    void Draw(sf::RenderWindow &window, const Camera &from) const override {};
    void Move(const v3f &to) { pos += to; }
};
