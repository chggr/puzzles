#include <stdio.h>
#include <stdlib.h>

// Task description: Given two straight line segments represented as a start
// point and an end point, compute the point of intersection if it exists.
//
// e.g. If the first line is defined as: {0. 0} {1, 1}
//      and the second line is defined as: {0, 1} {1, 0}
//      the method should return {0.5, 0.5}
//
// Solution: The implementation below first calculates the slope and y intercept
// for each line and then checks whether the slopes are the same. If indeed they
// are the same, then the two lines are parallel if the intercepts are different
// or on the same line if they are the same. On the contrary, if the slopes are
// different, then the two lines intersect somewhere on the plane. The
// intersection point is then calculated and returned only if it is within both
// line segments.

struct Point {
    double x;
    double y;
};

struct Line {
    struct Point start;
    struct Point end;
};

// Checks whether the middle is between start and end.
int is_between(double start, double middle, double end) {
    return start < end ?
           start <= middle && middle <= end :
           end <= middle && middle <= start;
}

// Checks whether the middle point is between start and end points.
int between(struct Point start, struct Point middle, struct Point end) {
    return is_between(start.x, middle.x, end.x) &&
           is_between(start.y, middle.y, end.y);
}

// Returns the intersections point of two lines if exists, NULL otherwise.
struct Point* intersection(struct Line a, struct Line b) {

    // If delta x is zero, the slope will be infinite (inf).
    double slopeA = (a.end.y - a.start.y) / (a.end.x - a.start.x);
    double slopeB = (b.end.y - b.start.y) / (b.end.x - b.start.x);
    double interceptA = a.end.y - slopeA * a.end.x;
    double interceptB = b.end.y - slopeB * b.end.x;

    struct Point* p = malloc(sizeof(struct Point));

    // If the slopes are the same, then lines are parallel. They will intercept
    // only if they have the same intercept and one overlaps with the other.
    if (slopeA == slopeB) {
        if (interceptA == interceptB) {
            if (between(a.start, b.end, a.end)) {
                p->x = b.end.x;
                p->y = b.end.y;
                return p;
            } else if (between(a.start, b.start, a.end)) {
                p->x = b.start.x;
                p->y = b.start.y;
                return p;
            }
        }
        free(p);
        return NULL;
    }

    // Calculate intersection coordinates, return the Point only if it is
    // within line segment range.
    p->x = (interceptB - interceptA) / (slopeA - slopeB);
    p->y = p->x * slopeA + interceptA;
    if (between(a.start, *p, a.end) &&
        between(b.start, *p, b.end)) {
        return p;
    }
    free(p);
    return NULL;
}

struct Line create_line(double startx,
                        double starty,
                        double endx,
                        double endy) {

    struct Point start;
    start.x = startx;
    start.y = starty;

    struct Point end;
    end.x = endx;
    end.y = endy;

    struct Line line;
    line.start = start;
    line.end = end;
    return line;
}

int test_intersection() {
    struct Line lineA = create_line(0, 0, 1, 1);
    struct Line lineB = create_line(0, 1, 1, 0);

    struct Point* p = intersection(lineA, lineB);
    if (p == NULL) return 0;

    int result = p->x == 0.5 && p->y == 0.5;
    free(p);
    return result;
}

int test_no_intersection() {
    struct Line lineA = create_line(0, 0, 1, 1);
    struct Line lineB = create_line(0, 3, 2, 1);

    struct Point* p = intersection(lineA, lineB);
    return p == NULL;
}

int test_same_no_intersection() {
    struct Line lineA = create_line(0, 0, 1, 1);
    struct Line lineB = create_line(2, 2, 5, 5);

    struct Point* p = intersection(lineA, lineB);
    return p == NULL;
}

int test_same_intersection() {
    struct Line lineA = create_line(0, 0, 1, 1);
    struct Line lineB = create_line(1, 1, 2, 2);

    struct Point* p = intersection(lineA, lineB);
    int result = p->x == 1.0 && p->y == 1.0;
    free(p);
    return result;
}

int test_parallel() {
    struct Line lineA = create_line(0, 0, 1, 1);
    struct Line lineB = create_line(0, 1, 1, 2);

    struct Point* p = intersection(lineA, lineB);
    return p == NULL;
}

int test_infinite_slope_no_intersection() {
    struct Line lineA = create_line(1, 1, 1, 2);
    struct Line lineB = create_line(1, 3, 1, 4);

    struct Point* p = intersection(lineA, lineB);
    return p == NULL;
}

int test_infinite_slope_intersection() {
    struct Line lineA = create_line(1, 1, 1, 2);
    struct Line lineB = create_line(1, 2, 1, 4);

    struct Point* p = intersection(lineA, lineB);
    int result = p->x == 1.0 && p->y == 2.0;
    free(p);
    return result;
}

int main() {
    int counter = 0;
    if (!test_intersection()) {
        printf("Intersection test failed!\n");
        counter++;
    }
    if (!test_no_intersection()) {
        printf("No intersection test failed!\n");
        counter++;
    }
    if (!test_same_no_intersection()) {
        printf("Same line, no intersection test failed!\n");
        counter++;
    }
    if (!test_same_intersection()) {
        printf("Same line, intersection test failed!\n");
        counter++;
    }
    if (!test_parallel()) {
        printf("Parallel line test failed!\n");
        counter++;
    }
    if (!test_infinite_slope_no_intersection()) {
        printf("Infinite slope, no intersection test failed!\n");
        counter++;
    }
    if (!test_infinite_slope_intersection()) {
        printf("Infinite slope, intersection test failed!\n");
        counter++;
    }
    printf("%d tests failed.\n", counter);
}

