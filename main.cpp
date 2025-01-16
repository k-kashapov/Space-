#include "entities.hpp"
#include "manager.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <set>

#define WIN_X 1400
#define WIN_Y 900
#define MAX_FPS 120

void print_v(const v3f &v) { std::cout << v.x << ", " << v.y << ", " << v.z << std::endl; }

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIN_X, WIN_Y, 1), "Space--");
    window.setFramerateLimit(MAX_FPS);
    window.setKeyRepeatEnabled(false);

    Manager man;

    for (int i = 0; i < 12000; i++) {
        std::random_device rd;
        std::default_random_engine e2(rd());
        std::uniform_real_distribution<> dist(-2e5, 2e5);

        man.AddObj<SpaceShip>("ship" + std::to_string(i),
                              {static_cast<float>(dist(e2)), static_cast<float>(dist(e2)),
                               static_cast<float>(dist(e2))});
    }

    auto player = man.AddObj<SpaceShip>("Player", {0, 0, -1000});
    player->SetSpd(100.0f);

    std::shared_ptr<Camera> cam = man.AddObj<Camera>("Camera", {0, 0, -200});
    cam->Follow(player.get());

    std::set<sf::Keyboard::Key> activeKeys;

    // Pause
    bool zaWardo = false;

    std::chrono::high_resolution_clock::time_point last;
    std::chrono::high_resolution_clock::time_point curr;
    float fps = MAX_FPS;

    sf::Font font;
    font.loadFromFile("Tecnica-55.ttf");
    auto text = sf::Text("FPS", font, 40);

    last = std::chrono::high_resolution_clock::now();

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

        // Calculate fps
        curr = std::chrono::high_resolution_clock::now();
        fps = 1.0e9 / std::chrono::duration_cast<std::chrono::nanoseconds>(curr - last).count();
        last = curr;

        if (zaWardo) {
            continue;
        }

        for (auto key : activeKeys) {
            switch (key) {
            case sf::Keyboard::Key::W:
                player->AddTorque(-player->GetBasis().as_vec(0));
                break;
            case sf::Keyboard::Key::S:
                player->AddTorque(player->GetBasis().as_vec(0));
                break;
            case sf::Keyboard::Key::A:
                player->AddTorque(-player->GetBasis().as_vec(2));
                break;
            case sf::Keyboard::Key::D:
                player->AddTorque(player->GetBasis().as_vec(2));
                break;
            case sf::Keyboard::Key::E:
                player->AddTorque(player->GetBasis().as_vec(1));
                break;
            case sf::Keyboard::Key::Q:
                player->AddTorque(-player->GetBasis().as_vec(1));
                break;
            case sf::Keyboard::Key::R:
                player->Accelerate();
                break;
            case sf::Keyboard::Key::F:
                player->Decelerate();
                break;
            default:
                break;
            }
        }

        // Clear screen
        window.clear();

        // Debug info
        v3f plr_pos = player->GetPos();
        text.setString("FPS: " + std::to_string(fps) +
                       "\nSpeed: " + std::to_string(std::log(player->GetSpd())) +
                       "\nX: " + std::to_string(plr_pos.x) + "\nY: " + std::to_string(plr_pos.y) +
                       "\nZ: " + std::to_string(plr_pos.z));

        window.draw(text);

        man.Draw(window, *cam);
        man.Update(1.0 / fps);

        // Update the window
        window.display();
    }
}
