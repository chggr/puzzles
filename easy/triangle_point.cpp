#include <cmath>
#include <iostream>

// Task description: Given three points in the plane that form a triangle, write
// a method to return whether a fourth point is within the triangle or not.
//
//E.g.
//               A * (10, 30)
//                / \
//               /   \
//              /     \       * (30, 20)
//             /  P    \
//            /   *     \
//           /   (7,5)   \
//    (0,0) *-------------* (20, 0)
//         B              C
//
// Solution: Let the three points that form the triangle be A / B / C and the
// fourth point P. The implementation below uses Gauss's area formula to
// calculate the total area of the triangle (ABC) and the areas of the smaller
// triangles formed using the target point (ABP, APC, PBC). If the target point
// is within the triangle, we expect the sum of areas of the smaller triangles
// to equal the total area of the large triangle, i.e. ABC = ABP + APC + PBC.

class Point {
    public:
        double x;
        double y;
        Point(double x, double y) : x(x), y(y) {}
};

// Calculates the area of a triangle using Gauss's area formula.
double area(Point a, Point b, Point c) {
    return std::abs(0.5 * (a.x * (b.y - c.y) +
                           b.x * (c.y - a.y) +
                           c.x * (a.y - b.y)));
}

bool is_inside(Point a, Point b, Point c, Point target) {
    double total = area(a, b, c);
    double part_a = area(target, b, c);
    double part_b = area(a, target, c);
    double part_c = area(a, b, target);
    return total == part_a + part_b + part_c;
}

bool test_inside() {
    return is_inside(Point(0,0), Point(10, 30), Point(20, 0), Point(7, 5));
}

bool test_outside() {
    return !is_inside(Point(0,0), Point(10, 30), Point(20, 0), Point(30, 20));
}

int main() {
    int counter = 0;
    if (!test_inside()) {
        counter++;
        std::cout << "Point inside triangle test failed." << std::endl;
    }
    if (!test_outside()) {
        counter++;
        std::cout << "Point outside triangle test failed." << std::endl;
    }
    std::cout << counter << " tests failed." << std::endl;
}

