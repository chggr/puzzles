#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

// Task description: Given N points in the plane, write a method to find out the
// closest pair of points and return their distance. The distance between two
// points can be computed as: sqrt((x1 - x2)^2 + (y1 - y2)^2)
//
// E.g. for points {1.0, 2.0} {1.0, 3.0} {-2.0, 3.0}
//      the method should return 1.0 between the first two points.
//
// Solution: The first implementation below uses a brute force approach to
// calculate the distance between all possible pairs of points and return the
// minimum. Using a double for loop, it goes through each point in the vector
// and pairs it with all other points. It then calculates their distance,
// keeping track and returning the minimum. The runtime complexity of this
// approach is O(N^2).
//
// The second implementation uses a divide and conquer approach to calculate
// the minimum distance between pairs of points in just O(N * logN * logN) time.
// The points vector is initially sorted according to the x coordinate. Then a
// recursive method is called which finds the middle point in the array and uses
// it to divide the array in two halves (LEFT and RIGHT) as shown in the graph
// below.
//
//                             MID
//           X        <    X    |         >            X
//                    <         |   X     >
//     X              <         |         >   X               X
//                X   <         |         >
//                    <         |         >
//                    <     X   |      X  >              X
//     X              <         |         >
//                    <  X      |         >         X
//         X          <         |         >                   X
// -------------------------------------------------------------
//                    <-------STRIP------->
// <-----------LEFT------------><-------------RIGHT------------>
//
//
// The same method is called recursively on the LEFT and RIGHT half to find the
// smallest distance in both sub-arrays. The minimum of those two is then used
// as an upper bound of the overall minimum distance. We then need to consider
// pairs of points where one is on the LEFT and the other is on the RIGHT. To
// do this, we create a second vector that contains all points whose distance
// from the MID is less than the upper bound found previously. These are the
// points that reside within the STRIP as shown in the graph above. To complete
// the calculation we need to find the smallest distance of any pair of points
// in the strip and pick the minimum distance overall (LEFT / RIGHT / STRIP).
//
// To find the smallest distance between points in the strip, we first sort the
// points based on their y coordinate. We then go through the points, computing
// the distance between each pair and keeping the minimum found so far. This is
// just an O(n) step because we use a short-circuit to terminate the inner for
// loop once the distance is greater than the minimum found so far. It can be
// geometrically proven that for every point in the strip we only need to check
// at most 7 points after it.
//
// The overall time complexity of this algorithm can be calculated as follows:
// The recursive method initially calls itself twice, then it finds all points
// in the STRIP in O(N), sorts these points in O(N * logN) and then finds the
// closest points in the strip in O(N). Therefore the time complexity T(N) of
// the algorithm can be written as follows:
//
// T(N) = 2 * T(N/2) + O(N) + O(N * logN) + O(N) =>
// T(N) = 2 * T(N/2) + O(N*logN) =>
// T(N) = T(N * logN * logN)

using namespace std;

class Point {
    public:
        double x;
        double y;
        Point(double x, double y) : x(x), y(y) {}
};

// Distance between two points.
double dist(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Brute force method to find the closest points.
double closest(vector<Point>& points) {
    double result = 0.0;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            double d = dist(points.at(i), points.at(j));
            if (result == 0.0 || result > d) result = d;
        }
    }
    return result;
}

bool compare_x(Point a, Point b) {
    return a.x < b.x;
}

bool compare_y(Point a, Point b) {
    return a.y < b.y;
}

// Find the distance between the closest points in the strip.
double closest_strip(vector<Point>& points, double strip_length) {
    sort(points.begin(), points.end(), compare_y);

    double min = strip_length;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            if (abs(points.at(i).y - points.at(j).y) > min) break;

            double d = dist(points.at(i), points.at(j));
            if (min > d) min = d;
        }
    }
    return min;
}

double closest_rec(vector<Point>& points, int start, int end) {

    // Base cases when there are less than three points.
    if (end <= start) return 0;
    if (end - start + 1 == 2) {
        return dist(points.at(start), points.at(end));
    }
    if (end - start + 1 == 3) {
        return min(dist(points.at(start), points.at(start + 1)),
                   min(dist(points.at(start), points.at(end)),
                       dist(points.at(start + 1), points.at(end))));
    }

    // Divide the plane in two and get the minimum distance for both.
    int mid = (start + end) / 2;
    double dist_left = closest_rec(points, start, mid);
    double dist_right = closest_rec(points, mid + 1, end);

    // Get the minimum distance from strip.
    double strip_length = min(dist_left, dist_right);
    double strip_x = (points.at(mid).x + points.at(mid + 1).x) / 2;
    vector<Point> strip;
    for (int i = start; i <= end; i++) {
        if (abs(points.at(i).x - strip_x) < strip_length) {
            strip.push_back(points.at(i));
        }
    }

    double dist_strip = closest_strip(strip, strip_length);
    return min(dist_strip, strip_length);
}

double closest_opt(vector<Point> points) {
    sort(points.begin(), points.end(), compare_x);
    return closest_rec(points, 0, points.size() - 1);
}

bool test_no_points() {
    vector<Point> points;

    return 0.0 == closest(points) &&
           0.0 == closest_opt(points);
}

bool test_one_point() {
    vector<Point> points;
    points.push_back(Point(1.0, 2.0));

    return 0.0 == closest(points) &&
           0.0 == closest_opt(points);
}

bool test_two_points() {
    vector<Point> points;
    points.push_back(Point(1.0, 2.0));
    points.push_back(Point(1.0, 3.0));

    return 1.0 == closest(points) &&
           1.0 == closest_opt(points);
}

bool test_three_points() {
    vector<Point> points;
    points.push_back(Point(1.0, 2.0));
    points.push_back(Point(1.0, 3.0));
    points.push_back(Point(-2.0, 3.0));

    return 1.0 == closest(points) &&
           1.0 == closest_opt(points);
}

bool test_many_points() {
    vector<Point> points;
    points.push_back(Point(1.0, 2.0));
    points.push_back(Point(1.0, 3.0));
    points.push_back(Point(5.0, 4.0));
    points.push_back(Point(2.0, 2.0));
    points.push_back(Point(-2.0, 2.0));
    points.push_back(Point(0.0, 0.0));

    return 1.0 == closest(points) &&
           1.0 == closest_opt(points);
}

bool test_random_points() {
    srand(time(NULL));

    // One thousand tests with up to one thousand points each.
    for (int i = 0; i < 1000; i++) {
        vector<Point> points;
        for (int i = 0; i < rand() % 1000; i++) {
            points.push_back(Point(rand() / RAND_MAX, rand() / RAND_MAX));
        }

        if (abs(closest(points) - closest_opt(points)) > 0.00001) return false;
    }
    return true;
}

int main() {
    int counter = 0;
    if (!test_no_points()) {
        cout << "No points test failed!" << endl;
        counter++;
    }
    if (!test_one_point()) {
        cout << "One point test failed!" << endl;
        counter++;
    }
    if (!test_two_points()) {
        cout << "Two points test failed!" << endl;
        counter++;
    }
    if (!test_three_points()) {
        cout << "Three points test failed!" << endl;
        counter++;
    }
    if (!test_many_points()) {
        cout << "Many points test failed!" << endl;
        counter++;
    }
    if (!test_random_points()) {
        cout << "Random points test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

