//
// Created by marina on 27.06.24.
//
#include <gtest/gtest.h>

#include "../polygon.h"

TEST(Simple, Triangle) {
    polygon polygon;
    polygon.draw_point({0, 0});
    polygon.draw_point({2, 0});
    polygon.draw_point({1, 2});

    auto result = polygon.calc_symmetric_axes();
    EXPECT_EQ(result.size(), 1);
    EXPECT_TRUE(result[0] == line({1.0, 0.0}, {1.0, 2.0}) ||
                result[0] == line({1.0, 2.0}, {1.0, 0.0}));
}

TEST(Simple, NonSymm) {
    polygon polygon;
    polygon.draw_point({0, 0});
    polygon.draw_point({2, 0});
    polygon.draw_point({2, 1});

    auto result = polygon.calc_symmetric_axes();
    EXPECT_EQ(result.size(), 0);
}

TEST(Simple, Square) {
    polygon polygon;
    polygon.draw_point({0, 0});
    polygon.draw_point({2, 0});
    polygon.draw_point({2, 2});
    polygon.draw_point({0, 2});

    auto result = polygon.calc_symmetric_axes();
    EXPECT_EQ(result.size(), 4);

    EXPECT_EQ(result[0], line({0.0, 0.0}, {2.0, 2.0}));
    EXPECT_EQ(result[1], line({0.0, 2.0}, {2.0, 0.0}));
    EXPECT_EQ(result[2], line({0.0, 1.0}, {2.0, 1.0}));
    EXPECT_EQ(result[3], line({1.0, 2.0}, {1.0, 0.0}));
}

TEST(Simple, Pentagon) {
    polygon polygon;
    polygon.draw_point({2, 0});
    polygon.draw_point({4, 0});
    polygon.draw_point({5, 1});
    polygon.draw_point({3, 2});
    polygon.draw_point({1, 1});

    auto result = polygon.calc_symmetric_axes();
    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], line({3.0, 2.0}, {3.0, 0.0}));
}

TEST(Simple, Hexagon) {
    polygon polygon;
    polygon.draw_point({2, 0});
    polygon.draw_point({4, 0});
    polygon.draw_point({5, 1});
    polygon.draw_point({4, 2});
    polygon.draw_point({2, 2});
    polygon.draw_point({1, 1});

    auto result = polygon.calc_symmetric_axes();
    EXPECT_EQ(result.size(), 2);

    EXPECT_EQ(result[0], line({1.0, 1.0}, {5.0, 1.0}));
    EXPECT_EQ(result[1], line({3.0, 2.0}, {3.0, 0.0}));
}

TEST(BigNumbers, Square) {
    polygon polygon;
    polygon.draw_point({11111111, 11111111});
    polygon.draw_point({33333333, 11111111});
    polygon.draw_point({33333333, 33333333});
    polygon.draw_point({11111111, 33333333});

    auto result = polygon.calc_symmetric_axes();
    EXPECT_EQ(result.size(), 4);

    EXPECT_EQ(result[0], line({11111111.0, 11111111.0}, {33333333.0, 33333333.0}));
    EXPECT_EQ(result[1], line({11111111.0, 33333333.0}, {33333333.0, 11111111.0}));
    EXPECT_EQ(result[2], line({11111111.0, 22222222.0}, {33333333.0, 22222222.0}));
    EXPECT_EQ(result[3], line({22222222.0, 33333333.0}, {22222222.0, 11111111.0}));
}

TEST(Accuracy, Square) {
    polygon polygon;
    polygon.draw_point({0.0, 0.0});
    polygon.draw_point({0.0000004, 0.0});
    polygon.draw_point({0.0000004, 0.0000004});
    polygon.draw_point({0.0, 0.0000004});

    auto result = polygon.calc_symmetric_axes();
    EXPECT_EQ(result.size(), 4);

    EXPECT_EQ(result[0], line({0.0, 0.0}, {0.0000004, 0.0000004}));
    EXPECT_EQ(result[1], line({0.0, 0.0000004}, {0.0000004, 0.0}));
    EXPECT_EQ(result[2], line({0.0, 0.0000002}, {0.0000004, 0.0000002}));
    EXPECT_EQ(result[3], line({0.0000002, 0.0000004}, {0.0000002, 0.0}));
}

int main() {
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}