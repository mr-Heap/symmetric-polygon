#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

//TODO:make more const
//TODO: naming
//TODO: определить и прописать точность в документации

std::pair<double, double> symm_point(double x, double y, double a, double b, double c) {
    // TODO: double -> non-big numbers, long double
    // TODO: вынести общие коэффициенты
    double d = a * a + b * b;

    double x_symm = x - 2 * a * (a * x + b * y + c) / d;
    double y_symm = y - 2 * b * (a * x + b * y + c) / d;
//    double dx_symm = x * static_cast<double>(d) - 2 * a * (a * x + b * y + c);
//    double dy_symm = y * static_cast<double>(d) - 2 * b * (a * x + b * y + c);
    return {x_symm, y_symm};
}

bool isSymmetricConvexPolygon(const std::vector<std::pair<double, double>> &points,
                              const std::pair<double, double> &line_point1,
                              const std::pair<double, double> &line_point2) {
    size_t n = points.size();
    double x1 = line_point1.first, y1 = line_point1.second;
    double x2 = line_point2.first, y2 = line_point2.second;

    double a = y2 - y1;
    double b = x1 - x2;
    double c = x2 * y1 - x1 * y2;

    for (int i = 0; i < n; ++i) {
        auto p1 = points[i];
        auto reflected_p1 = symm_point(p1.first, p1.second, a, b, c);
        if (!std::any_of(points.begin(), points.end(), [&](const std::pair<double, double> &p) {
            return fabs(p.first - reflected_p1.first) < 1e-9 && fabs(p.second - reflected_p1.second) < 1e-9;
        })) {
            return false;
        }
    }

    return true;
}

std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>
findSymmetryAxes(const std::vector<std::pair<double, double>> &points) {
    std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> axes;
    size_t n = points.size();

    if (n % 2 == 1) {
        for (int i = 0; i <= n / 2 + 1; ++i) {
            auto p0 = points[i];
            size_t ind1 = (i + n / 2) % n;
            size_t ind2 = (ind1 + 1) % n;
            std::pair<double, double> p1{(points[ind1].first + points[ind2].first) / 2,
                                         (points[ind1].second + points[ind2].second) / 2};
            if (isSymmetricConvexPolygon(points, p0, p1)) {
                axes.emplace_back(p0, p1);
            }
            std::cout << p0.first << ' ' << p0.second << " / " << p1.first << ' ' << p1.second << ' '
                      << isSymmetricConvexPolygon(points, p0, p1) << '\n';
        }
    } else {
        for (int i = 0; i < n / 2; ++i) {
            auto p0 = points[i];
            auto p1 = points[i + n / 2];
            if (isSymmetricConvexPolygon(points, p0, p1)) {
                axes.emplace_back(p0, p1);
            }
            std::cout << p0.first << ' ' << p0.second << " / " << p1.first << ' ' << p1.second << ' '
                      << isSymmetricConvexPolygon(points, p0, p1) << '\n';
        }
        for (int i = 0; i < n / 2; ++i) {
            std::pair<double, double> p0{(points[i].first + points[i + 1].first) / 2,
                                         (points[i].second + points[i + 1].second) / 2};
            std::pair<double, double> p1{(points[i + n / 2].first + points[i + n / 2 + 1].first) / 2,
                                         (points[i + n / 2].second + points[i + n / 2 + 1].second) / 2};
            if (isSymmetricConvexPolygon(points, p0, p1)) {
                axes.emplace_back(p0, p1);
            }
            std::cout << p0.first << ' ' << p0.second << " / " << p1.first << ' ' << p1.second << ' '
                      << isSymmetricConvexPolygon(points, p0, p1) << '\n';
        }
    }

    return axes;
}

int main() {
    // TODO: get routing procedure
    std::vector<std::pair<double, double>> points = {{1, 0},
                                                     {2, 0},
                                                     {3, 1},
                                                     {1.5, 2},
                                                     {0, 1}};
    findSymmetryAxes(points);


    return 0;
}