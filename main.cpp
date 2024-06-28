//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <filesystem>
//#include "polygon.h"
//
//int main(int argc, char* args[]) {
//
//    if (argc != 2) {
//        std::cerr << "Invalid input, usage: <file_name>\n";
//        return 1;
//    }
//    if (std::filesystem::exists(args[1])) {
//        std::cerr << "File is not exist\n";
//        return 1;
//    }
//    std::ifstream in(args[1]);
//
//    polygon polygon;
//
//    double x, y;
//    while (in >> x >> y) {
//        polygon.draw_point({x, y});
//    }
//    in.close();
//
//    std::vector<line> axes = polygon.calc_symmetric_axes();
//    if (axes.empty()) {
//        std::cout << "non-symmetric";
//    } else {
//        for (line &ax: axes) {
//            point from = ax.first;
//            point to = ax.second;
//            std::cout << from.x << " " << from.y << " - " << to.x << " " << to.y << "\n";
//        }
//    }
//
//    return 0;
//}
