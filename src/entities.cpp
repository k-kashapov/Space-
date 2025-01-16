#include "entities.hpp"
#include "linalg.hpp"

void SpaceShip::Draw(sf::RenderWindow &window, const Camera &from) const {
    static const v2f win_size = v2f(window.getSize()) / 2.0f;

    v3f dist = pos - from.GetPos();
    if (norm_l1(dist) > from.GetRenderDist()) {
        return;
    }

    std::vector<v2f> projections;
    m33 bas = from.GetBasis();

    for (size_t point = 0; point < model.size(); ++point) {
        v3f l = pos + matmul(model[point], basis) - from.GetPos();
        l /= norm(l);

        // Intersect with plane
        float d = from.GetD() / dot(l, bas.z());

        if (d < EPS || d > win_size.x * 1.3) {
            break;
        }

        // Vector from center to intersection point
        v3f p = l * d - bas.z() * from.GetD();

        v2f pixel = {dot(p, bas.x()), dot(p, bas.y())};

        projections.push_back(pixel + win_size);
    }

    if (projections.size() == model.size()) {
        window.draw(model.ToPrimitives2D(projections));
    }
}
