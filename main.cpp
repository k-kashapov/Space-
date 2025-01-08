#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

#define EPS 1e-5
#define WIN_X 800
#define WIN_Y 600

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

float dot(const v3f& a, const v3f& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float norm2(const v3f& v) {
    return dot(v, v);
}

float norm(const v3f& v) {
    return std::sqrt(norm2(v));
}

void SpaceShip::Draw(sf::RenderWindow& window, const Camera& from) const {
    std::vector<v2f> projections(model.size());
    m33 bas = from.getBasis();

    for (size_t point = 0; point < model.size(); ++point) {
        v3f l = model[point] - from.getPos();
        l /= norm(l);

        // Intersect with plane
        float d = from.D / dot(l, bas[2]);

        // Vector from center to intersection point
        v3f p = l * d - bas[2] * from.D;

        projections[point] = {dot(p, bas[0]) * 10 + WIN_X / 2, dot(p, bas[1]) * 10 + WIN_Y / 2};
    }

    sf::VertexArray lines(sf::Lines, (model.size() * (model.size() - 1)));

    size_t line_num = 0;

    for (size_t i = 0; i < model.size() - 1; ++i) {
        for (size_t j = i + 1; j < model.size(); ++j) {
            lines[line_num++].position = projections[i];
            lines[line_num++].position = projections[j];
        }
    }

    window.draw(lines);
}

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({WIN_X, WIN_Y}), "Space++");

    SpaceShip ship;
    Camera cam;

    cam.setPos(v3f{0, 0, -100});

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                float spd = cam.getSpd();

                if (event.key.code == sf::Keyboard::Key::W) {
                    cam.Move(v3f(0.0, spd, 0.0));
                }
                if (event.key.code == sf::Keyboard::Key::S) {
                    cam.Move(v3f(0.0, -spd, 0.0));
                }
                if (event.key.code == sf::Keyboard::Key::A) {
                    cam.Move(v3f(-spd, 0.0, 0.0));
                }
                if (event.key.code == sf::Keyboard::Key::D) {
                    cam.Move(v3f(spd, 0.0, 0.0));
                }
                if (event.key.code == sf::Keyboard::Key::Q) {
                    cam.Move(v3f(0.0, 0.0, -spd));
                }
                if (event.key.code == sf::Keyboard::Key::E) {
                    cam.Move(v3f(0.0, 0.0, spd));
                }
            }
        }

        // Clear screen
        window.clear();

        ship.Draw(window, cam);
 
        // Update the window
        window.display();
    }
}
