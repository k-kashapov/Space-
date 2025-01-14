#include "entities.hpp"
#include "linalg.hpp"

void SpaceShip::Draw(sf::RenderWindow &window, const Camera &from) const {
    v2f win_size = v2f(window.getSize());
    win_size.x /= 2.0;
    win_size.y /= 2.0;

    std::vector<v2f> projections(model.size());
    m33 bas = from.GetBasis();

    for (size_t point = 0; point < model.size(); ++point) {
        v3f l = pos + matmul(model[point], basis) - from.GetPos();
        l /= norm(l);

        // Intersect with plane
        float d = from.GetD() / dot(l, bas.as_vec(2));

        if (d < 0)
            continue;

        // Vector from center to intersection point
        v3f p = l * d - bas.as_vec(2) * from.GetD();

        projections[point] = {dot(p, bas.as_vec(0)) * 10, dot(p, bas.as_vec(1)) * 10};
        projections[point] += win_size;
    }

    window.draw(model.ToPrimitives2D(projections));
}
