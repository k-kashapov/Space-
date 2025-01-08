#include "entities.hpp"
#include "linalg.hpp"

void SpaceShip::Draw(sf::RenderWindow& window, const Camera& from) const {
    v2f win_size = v2f(window.getSize());
    win_size.x /= 2.0;
    win_size.y /= 2.0;

    std::vector<v2f> projections(model.size());
    m33 bas = from.getBasis();

    for (size_t point = 0; point < model.size(); ++point) {
        v3f l = model[point] - from.getPos();
        l /= norm(l);

        // Intersect with plane
        float d = from.D / dot(l, bas[2]);

        // Vector from center to intersection point
        v3f p = l * d - bas[2] * from.D;

        projections[point] = {dot(p, bas[0]) * 10, dot(p, bas[1]) * 10};
        projections[point] += win_size;
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

