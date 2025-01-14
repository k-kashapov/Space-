#include "entities.hpp"
#include "manager.hpp"
#include <iostream>
#include <set>

#define WIN_X 800
#define WIN_Y 600
#define MAX_FPS 60

void print_v(const v3f &v) { std::cout << v.x << ", " << v.y << ", " << v.z << std::endl; }

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIN_X, WIN_Y, 1), "Space--");
    window.setFramerateLimit(MAX_FPS);
    window.setKeyRepeatEnabled(false);

    Manager man;
    auto ship1 = man.AddObj<SpaceShip>("ship1", {0, 0, 0});
    auto ship2 = man.AddObj<SpaceShip>("ship2", {0, 2000, 0});
    auto ship3 = man.AddObj<SpaceShip>("ship3", {0, 1200, 1200});

    man.AddObj<SpaceShip>("ship4", {0, -1200, 1200});

    man.AddObj<SpaceShip>("ship5", {1500, 0, 0});

    auto player = man.AddObj<SpaceShip>("Player", {0, 0, -1000});

    std::shared_ptr<Camera> cam = man.AddObj<Camera>("Camera", {0, 0, -200});
    cam->Follow(player.get());

    std::set<sf::Keyboard::Key> activeKeys;

    bool zaWardo = false;

    float time = 0.0;
    float delta = 1.0 / MAX_FPS;
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::P) {
                zaWardo = !zaWardo;
            }

            if (event.type == sf::Event::KeyPressed) {
                activeKeys.insert(event.key.code);
            } else if (event.type == sf::Event::KeyReleased) {
                activeKeys.erase(event.key.code);
            }
        }

        for (auto key : activeKeys) {
            switch (key) {
            case sf::Keyboard::Key::W:
                player->Rotate(player->GetBasis().as_vec(0), -player->GetRotSpd());
                break;
            case sf::Keyboard::Key::S:
                player->Rotate(player->GetBasis().as_vec(0), player->GetRotSpd());
                break;
            case sf::Keyboard::Key::A:
                player->Rotate(player->GetBasis().as_vec(2), -player->GetRotSpd());
                break;
            case sf::Keyboard::Key::D:
                player->Rotate(player->GetBasis().as_vec(2), player->GetRotSpd());
                break;
            default:
                break;
            }
        }

        if (zaWardo)
            continue;

        time += 1.0 / MAX_FPS;

        // Clear screen
        window.clear();

        // TODO: add actual update functions
        man.Draw(window, *cam);
        man.Update(1.0 / MAX_FPS);

        v3f newpos = {100 * sinf(time), 100 * cosf(time), 120};
        ship3->SetPos(newpos);

        ship1->Rotate(v3f{1, 0, 0}, 0.01);
        ship2->Rotate(v3f{0, 1, 0}, 0.01);

        player->SetPos(player->GetPos() + player->GetBasis().as_vec(2) * player->GetSpd());

        // Update the window
        window.display();
    }
}
