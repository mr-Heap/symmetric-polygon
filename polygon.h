//
// Created by marina on 26.06.24.
//
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_set>

/**
 * @class point
 * @brief represents a point in the plane
 *
 * two double fields: x and y coordinates
 */
struct point {
    explicit point(std::pair<double, double> point) : x(point.first), y(point.second) {}

    point(double x, double y) : x(x), y(y) {}

    bool operator==(const point &other) const {
        return x == other.x && y == other.y;
    }

    double x;
    double y;
};

const double INF = 1e10;

struct point_hash {
    std::size_t operator()(const point &p) const {
        double x = std::round(p.x * INF) / INF;
        double y = std::round(p.y * INF) / INF;
        return 31 * std::hash<double>{}(x) + std::hash<double>{}(y);
    }
};

/**
 * @class line
 * @brief represents a line in the plane
 *
 * two point fields: two points on the line
 */
struct line {
    point first;
    point second;

    line(point a, point b) : first(a), second(b) {}

    bool operator==(const line &other) const {
        return first == other.first && second == other.second;
    }

    /**
     * @brief Method to obtain a value of an a-coefficient of line
     * @return a value of an a-coefficient
     */
    [[nodiscard]] double a() const {
        return second.y - first.y;
    }

    /**
     * @brief Method to obtain a value of b-coefficient of line
     * @return a value of a b-coefficient
     */
    [[nodiscard]] double b() const {
        return first.x - second.x;
    }

    /**
     * @brief Method to obtain a value of c-coefficient of line
     * @return a value of an c-coefficient
     */
    [[nodiscard]] double c() const {
        return second.x * first.y - first.x * second.y;
    }
};

/**
 * @class polygon
 * @brief represents a polygon in the plane
 *
 * Main class that stores all points and provides methods in particular getting all symmetric axes
 */
class polygon {
public:

    /**
     * @brief Add point to the polygon
     * @param a new point of polygon
     */
    void draw_point(point &&point) {
        points.emplace_back(std::move(point));
    }

    /**
     * @brief Get all symmetric axes of the polygon
     * @return a vector of symmetric axes of the polygon -- vector of lines
     */
    std::vector<line> calc_symmetric_axes();

private:

    bool is_symmetry_axis(const line &line, const std::unordered_set<point, point_hash> &set);

    std::vector<point> points;
};

