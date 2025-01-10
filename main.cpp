#include "entities.hpp"
#include <iostream>

#define WIN_X 800
#define WIN_Y 600

void print_v(const v3f &v) { std::cout << v.x << ", " << v.y << ", " << v.z << std::endl; }

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({WIN_X, WIN_Y}), "Space--");

    SpaceShip ship1;
    SpaceShip ship2;
    SpaceShip ship3;

    ship1.setPos(v3f{0, 0, 0});
    ship2.setPos(v3f{0, 200, 0});
    ship3.setPos(v3f{0, 120, 120});

    Camera cam;

    cam.setPos(v3f{0, 0, -200});

    float time = 0.0;

    // Start the game loop
    while (window.isOpen()) {
        time += 0.001;
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                float spd = cam.getSpd();

                if (event.key.code == sf::Keyboard::Key::W) {
                    cam.Move(spd * cam.getBasis().as_vec(2));
                }
                if (event.key.code == sf::Keyboard::Key::S) {
                    cam.Move(-spd * cam.getBasis().as_vec(2));
                }
                if (event.key.code == sf::Keyboard::Key::E) {
                    cam.Move(spd * cam.getBasis().as_vec(0));
                }
                if (event.key.code == sf::Keyboard::Key::Q) {
                    cam.Move(-spd * cam.getBasis().as_vec(0));
                }
                if (event.key.code == sf::Keyboard::Key::R) {
                    cam.Move(-spd * cam.getBasis().as_vec(1));
                }
                if (event.key.code == sf::Keyboard::Key::F) {
                    cam.Move(spd * cam.getBasis().as_vec(1));
                }
                if (event.key.code == sf::Keyboard::Key::A) {
                    cam.Rotate(-cam.getBasis().as_vec(1));
                }
                if (event.key.code == sf::Keyboard::Key::D) {
                    cam.Rotate(cam.getBasis().as_vec(1));
                }
                if (event.key.code == sf::Keyboard::Key::C) {
                    cam.Rotate(cam.getBasis().as_vec(2));
                }
                if (event.key.code == sf::Keyboard::Key::Z) {
                    cam.Rotate(-cam.getBasis().as_vec(2));
                }
            }
        }

        // Clear screen
        window.clear();

        ship1.Draw(window, cam);
        ship2.Draw(window, cam);
        ship3.Draw(window, cam);

        v3f newpos = {100 * sinf(time / 5), 100 * cosf(time / 5), 120};

        ship1.Rotate(v3f{1, 0, 0}, 0.0001);
        ship2.Rotate(v3f{0, 1, 0}, 0.0001);
        ship3.setPos(newpos);

        // Update the window
        window.display();
    }
}
