#include "entities.hpp"

#define WIN_X 800
#define WIN_Y 600

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
