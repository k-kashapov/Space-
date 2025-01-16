#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <algorithm>

#include "linalg.hpp"
#include "models.hpp"

class Camera;

class SpaceObj {
  protected:
    v3f pos;
    m33 basis = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
    };

    // Linear speed and acceleration
    float mov_acc = 1.03;
    float mov_spd = 0.0f;

    // Angular speed and acceleration
    float ang_acc = 0.08;
    v3f ang_spd;

    float ang_damp = 1.05;

  public:
    std::string name_;

    SpaceObj(std::string name, v3f position) : pos(position), name_(name) {};

    v3f GetPos() const { return pos; }
    void SetPos(const v3f &to) { pos = to; }

    m33 GetBasis() const { return basis; }
    void SetBasis(const m33 &new_b) { basis = new_b; }

    float GetSpd() const { return mov_spd; }
    void SetSpd(float spd) { mov_spd = spd; }

    v3f GetAngSpd() const { return ang_spd; }
    void SetRotSpd(const v3f &spd) { ang_spd = spd; }

    void Rotate(const v3f &axis, float angle) { basis = rotate(basis, axis, angle); }

    void AddTorque(const v3f &axis) { ang_spd += normalized(axis) * ang_acc; }

    void Accelerate() {
        if (mov_spd < EPS) {
            mov_spd = mov_acc;
        }

        mov_spd *= mov_acc;
    }

    void Decelerate() { mov_spd /= mov_acc; }

    virtual void Draw(sf::RenderWindow &window, const Camera &from) const = 0;
    virtual void Update(float delta) = 0;
    virtual ~SpaceObj() {};
};

static const std::initializer_list<v3f> DefaultShipModel = {
    {-100, 0, 0}, {0, 100, 0}, {100, 0, 0}, {0, -100, 0}, {0, 0, 100}, {0, 0, -100}};

class SpaceShip : public SpaceObj {
    FullMeshModel model;

  public:
    SpaceShip(std::string name, v3f position) : SpaceObj(name, position), model(DefaultShipModel) {}

    void Draw(sf::RenderWindow &window, const Camera &from) const override;
    void Update(float delta) override {
        pos += basis.as_vec(2) * mov_spd * delta;

        float l = norm(ang_spd);
        if (l > 1e-3) {
            Rotate(ang_spd, l * delta);
            ang_spd /= ang_damp;
        }
    };
};

class Camera final : public SpaceObj {
    const SpaceObj *target = nullptr;

    const float follow_dist = 150.0;
    const float follow_speed = 9e-3;
    const float follow_rot_spd = 2.1;

    // Distance to plane
    float D = 450.0;

    float render_dist = 2e5;

    void rotateToMatch(v3f a, v3f b, float delta) {
        v3f diff = normalized(a) - normalized(b);
        float l = norm(diff);

        if (l > 1e-5) {
            Rotate(-a * b, follow_rot_spd * l * delta);
        }
    }

  public:
    Camera(std::string name, v3f position) : SpaceObj(name, position) {}

    void Follow(const SpaceObj *obj) { target = obj; }

    float GetD() const { return D; }
    void SetD(float newD) { D = std::clamp(newD, 100.0f, 800.0f); }

    float GetRenderDist() const { return render_dist; }

    void Move(const v3f &to) { pos += to; }

    void Draw([[maybe_unused]] sf::RenderWindow &window,
              [[maybe_unused]] const Camera &from) const override {};

    void Update(float delta) override {
        m33 tgt_basis = target->GetBasis();
        v3f tgt_Oy = tgt_basis.as_vec(1);
        v3f tgt_Oz = tgt_basis.as_vec(2);

        v3f tgt_point = target->GetPos() - follow_dist * (tgt_Oy + tgt_Oz);

        v3f diff = tgt_point - pos;
        float l = norm(diff);
        Move(diff * l * follow_speed * delta);

        v3f my_Oy = basis.as_vec(1);
        v3f my_Oz = basis.as_vec(2);

        rotateToMatch(tgt_Oz, my_Oz, delta);
        rotateToMatch(tgt_Oy, my_Oy, delta);
    };
};

class Player final : public SpaceShip {
  public:
    void Draw([[maybe_unused]] sf::RenderWindow &window,
              [[maybe_unused]] const Camera &from) const override {};
    void Move(const v3f &to) { pos += to; }
};
