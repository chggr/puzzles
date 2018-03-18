import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: Given a two dimensional graph with many points on it,
// find a line that passes through the most number of points.
//
// Solution: In the implementation below we have defined two classes: Point and
// Line. We go through all pairs of Points in the graph, calculating the Line
// that passes through them and using a Map to count the number of times each
// line has been seen.
//
// Two Lines are equal if they have the same slope and y-intercept. These are
// represented in the Line class using doubles, but floating point numbers
// cannot always be represented accurately in binary. Therefore an improvement
// to the solution below would be to consider two Lines equal if their slope
// and intercept are within an epsilon value of each other.

public class BestLine {

    private static final class Point {
        public double x;
        public double y;

        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    }

    private static final class Line {
        public double slope;
        public double intercept;

        public Line(double slope, double intercept) {
            this.slope = slope;
            this.intercept = intercept;
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Line)) return false;

            Line other = (Line) o;
            return this.slope == other.slope &&
                   this.intercept == other.intercept;
        }

        @Override
        public int hashCode() {
            int hashcode = 37;
            hashcode = hashcode * 17 + Double.valueOf(slope).hashCode();
            hashcode = hashcode * 17 + Double.valueOf(intercept).hashCode();
            return hashcode;
        }
    }

    private static Line find(List<Point> points) {
        Map<Line, Integer> map = new HashMap<>();
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                Point a = points.get(i);
                Point b = points.get(j);

                double slope = (a.y - b.y) / (a.x - b.x);
                double intercept = a.y - slope * a.x;
                Line line = new Line(slope, intercept);

                Integer existing = map.get(line);
                map.put(line, existing == null ? 1 : existing + 1);
            }
        }

        int maxLines = 0;
        Line bestLine = null;
        for (Map.Entry<Line, Integer> e : map.entrySet()) {
            if (e.getValue() > maxLines) {
               bestLine = e.getKey();
               maxLines = e.getValue();
            }
        }
        return bestLine;
    }

    private static boolean testOnePoint() {
        Line result = find(Arrays.asList(new Point(1, 1)));
        return result == null;
    }

    private static boolean testTwoPoints() {
        Line result = find(Arrays.asList(new Point(1, 1), new Point(2, 2)));
        return result.slope == 1.0 &&
               result.intercept == 0.0;
    }

    private static boolean testThreePoints() {
        Line result = find(Arrays.asList(new Point(1, 1),
                                         new Point(2, 2),
                                         new Point(3, 3)));
        return result.slope == 1.0 &&
               result.intercept == 0.0;
    }

    private static boolean testFourPoints() {
        Line result = find(Arrays.asList(new Point(1, 1),
                                         new Point(2, 2),
                                         new Point(3, 3),
                                         new Point(2, 1)));
        return result.slope == 1.0 &&
               result.intercept == 0.0;
    }

    private static boolean testInfiniteSlope() {
        Line result = find(Arrays.asList(new Point(2, 5),
                                         new Point(2, 2),
                                         new Point(3, 3),
                                         new Point(2, 1)));
        return result.slope == Double.POSITIVE_INFINITY &&
               result.intercept == Double.NEGATIVE_INFINITY;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testOnePoint()) {
            counter++;
            System.out.println("One point test failed!");
        }
        if (!testTwoPoints()) {
            counter++;
            System.out.println("Two points test failed!");
        }
        if (!testThreePoints()) {
            counter++;
            System.out.println("Three points test failed!");
        }
        if (!testFourPoints()) {
            counter++;
            System.out.println("Four points test failed!");
        }
        if (!testInfiniteSlope()) {
            counter++;
            System.out.println("Infinite slope test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

