//
// Created by marina on 27.06.24.
//
#include "polygon.h"

bool polygon::is_symmetry_axis(const line &line, const std::unordered_set<point, point_hash> &set) {
    return std::all_of(points.begin(), points.end(), [&set, &line](point & point) {
        double a = line.a();
        double b = line.b();
        double c = line.c();

        double normal_length_sqr = a * a + b * b;
        double factor = (a * point.x + b * point.y + c) / normal_length_sqr;
        double x = point.x - 2 * a * factor;
        double y = point.y - 2 * b * factor;
        return set.count({x, y});
    });
}

std::vector<line> polygon::calc_symmetric_axes() {

    // order of evasion
    auto start_point = points[0];
    std::sort(points.begin(), points.end(), [start_point](point a, point b) {
        return (a.x - start_point.x) * (b.y - start_point.y) - (a.y - start_point.y) * (b.x - start_point.x) < 0;
    });

    std::unordered_set<point, point_hash> points_on_contour;
    for (auto& point : points) {
        points_on_contour.insert(point);
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
            if (is_symmetry_axis(line(p0, p1), points_on_contour)) {
                axes.emplace_back(p0, p1);
            }
        }
    } else {
        for (int i = 0; i < n / 2; ++i) {
            size_t ind = (i + n / 2) % n;
            auto p0 = points[i];
            auto p1 = points[ind];
            if (is_symmetry_axis(line(p0, p1), points_on_contour)) {
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
            if (is_symmetry_axis(line(p0, p1), points_on_contour)) {
                axes.emplace_back(p0, p1);
            }
        }
    }

    return axes;
}

