#include <iostream>
#include <vector>
#include <fstream>
#include "polygon.h"

int main(int argc, char* args[]) {

    // TODO: порядок обхода
    std::ifstream in(args[1]);

    polygon polygon;

    double x, y;
    while (in >> x >> y) {
        polygon.draw_point({x, y});
    }
    in.close();

    std::vector<line> axes = polygon.get_symmetric_axes();
    if (axes.empty()) {
        std::cout << "non-symmetric";
    } else {
        for (line &ax: axes) {
            point from = ax.first;
            point to = ax.second;
            std::cout << from.x << " " << from.y << " - " << to.x << " " << to.y << "\n";
        }
    }

    return 0;
}
