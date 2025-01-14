#include "models.hpp"

sf::VertexArray FullMeshModel::ToPrimitives2D(std::vector<v2f> screen_space_pts) const {
    sf::VertexArray lines(sf::Lines, (points.size() * (points.size() - 1)));

    size_t line_num = 0;

    for (size_t i = 0; i < points.size() - 1; ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            lines[line_num++].position = screen_space_pts[i];
            lines[line_num++].position = screen_space_pts[j];
        }
    }

    return lines;
}
