#include <iostream>

// Task description: Given two rectangles defined by their upper left (UL) and
// lower right (LR) points, write a method to check whether they overlap. The
// rectangles' edges will always be parallel to the x or y axis.
//
// E.g. The two rectangles below do not overlap:
//      Rectangle(Point(0.0, 1.0), Point(1.0, 0.0))
//      Rectangle(Point(0.0, 10.0), Point(1.0, 5.0))
//
//      The two rectangles below overlap:
//      Rectangle(Point(0.0, 5.0), Point(5.0, 0.0))
//      Rectangle(Point(3.0, 8.0), Point(8.0, 3.0))
//
// Solution: In the implementation below we first define two classes: Point and
// Rectangle. There are many different ways that the two rectangles can overlap:
// on one corner, on two corners, on all corners (i.e. one rectangle inside the
// other) or on no corners (i.e. like a cross). We could explicitly test for
// each one of those configurations, but it would be easier to just define when
// the two rectangles do not overlap and then negate that.
//
// Two rectangles A and B do not overlap if:
// - A's UL corner y is less than B's LR corner y
// - B's UL corner y is less than A's LR corner y
// - A's LR corner x is less than B's UL corner x
// - B's LR corner x is less than A's UL corner x

class Point {

    private:
        double x;
        double y;

    public:
        Point(double x, double y) : x(x), y(y) {}
        double getX() { return x; }
        double getY() { return y; }
};

class Rectangle {

    private:
        Point ul;
        Point lr;

    public:
        Rectangle(Point ul, Point lr) : ul(ul), lr(lr) {}
        Point getUL() { return ul; }
        Point getLR() { return lr; }
        bool isValid() {
            return ul.getX() <= lr.getX() &&
                   ul.getY() >= lr.getY();
        }
};

bool overlap(Rectangle a, Rectangle b) {
    return !(a.getUL().getY() < b.getLR().getY() ||
             b.getUL().getY() < a.getLR().getY() ||
             a.getLR().getX() < b.getUL().getX() ||
             b.getLR().getX() < a.getUL().getX());
}

bool test_no_overlap() {
    Rectangle a(Point(0.0, 1.0), Point(1.0, 0.0));
    Rectangle b(Point(0.0, 10.0), Point(1.0, 5.0));
    return a.isValid() && b.isValid() && !overlap(a, b);
}

bool test_cross_overlap() {
    Rectangle a(Point(2.0, 10.0), Point(3.0, 0.0));
    Rectangle b(Point(1.0, 6.0), Point(4.0, 5.0));
    return a.isValid() && b.isValid() && overlap(a, b);
}

bool test_full_overlap() {
    Rectangle a(Point(1.0, 5.0), Point(2.0, 4.0));
    Rectangle b(Point(0.0, 6.0), Point(3.0, 3.0));
    return a.isValid() && b.isValid() && overlap(a, b);
}

bool test_same_rectangle() {
    Rectangle a(Point(1.0, 5.0), Point(2.0, 4.0));
    return a.isValid() && overlap(a, a);
}

bool test_one_corner_overlap() {
    Rectangle a(Point(0.0, 5.0), Point(5.0, 0.0));
    Rectangle b(Point(3.0, 8.0), Point(8.0, 3.0));
    return a.isValid() && b.isValid() && overlap(a, b);
}

bool test_two_corners_overlap() {
    Rectangle a(Point(1.0, 5.0), Point(5.0, 1.0));
    Rectangle b(Point(0.0, 3.0), Point(6.0, 0.0));
    return a.isValid() && b.isValid() && overlap(a, b);
}

int main() {
    int counter = 0;
    if (!test_no_overlap()) {
        std::cout << "No overlap test failed!" << std::endl;
        counter++;
    }
    if (!test_cross_overlap()) {
        std::cout << "Cross overlap test failed!" << std::endl;
        counter++;
    }
    if (!test_same_rectangle()) {
        std::cout << "Same rectangle overlap test failed!" << std::endl;
        counter++;
    }
    if (!test_full_overlap()) {
        std::cout << "Full overlap test failed!" << std::endl;
        counter++;
    }
    if (!test_one_corner_overlap()) {
        std::cout << "One corner overlap test failed!" << std::endl;
        counter++;
    }
    if (!test_two_corners_overlap()) {
        std::cout << "Two corners overlap test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

