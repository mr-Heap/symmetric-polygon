//
// Created by marina on 27.06.24.
//
#include "polygon.h"

bool polygon::is_symmetry_axis(const line &line, const std::unordered_set<point> &set) {
    return std::all_of(points.begin(), points.end(), [&set, &line](point & point) {
        double a = line.get_a();
        double b = line.get_b();
        double c = line.get_c();

        double d = a * a + b * b;
        double factor = (a * point.x + b * point.y + c) / d;
        double x = point.x - 2 * a * factor;
        double y = point.y - 2 * b * factor;
        return set.count({x, y});
    });
}

std::vector<line> polygon::get_symmetric_axes() {
    std::unordered_set<point> set;
    for (auto& point : points) {
        set.insert(point);
    }
    std::vector<line> axes;
    size_t n = points.size();

    if (n % 2 == 1) {
        for (int i = 0; i <= n / 2 + 1; ++i) {
            point p0 = points[i];
            size_t ind1 = (i + n / 2) % n;
            size_t ind2 = (ind1 + 1) % n;
            point p1{(points[ind1].x + points[ind2].x) / 2,
                     (points[ind1].y + points[ind2].y) / 2};
            if (is_symmetry_axis(line(p0, p1), set)) {
                axes.emplace_back(p0, p1);
            }
        }
    } else {
        for (int i = 0; i < n / 2; ++i) {
            size_t ind = (i + n / 2) % n;
            auto p0 = points[i];
            auto p1 = points[ind];
            if (is_symmetry_axis(line(p0, p1), set)) {
                axes.emplace_back(p0, p1);
            }
        }
        for (int i = 0; i < n / 2; ++i) {
            size_t ind1 = (i + n / 2) % n;
            size_t ind2 = (ind1 + 1) % n;
            point p0{(points[i].x + points[i + 1].x) / 2,
                     (points[i].y + points[i + 1].y) / 2};
            point p1{(points[ind1].x + points[ind2].x) / 2,
                     (points[ind1].y + points[ind2].y) / 2};
            if (is_symmetry_axis(line(p0, p1), set)) {
                axes.emplace_back(p0, p1);
            }
        }
    }

    return axes;
}

