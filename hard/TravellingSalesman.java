import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Stack;

// Task description: A salesman needs to travel to N cities. The order in which
// he visits each city does not matter as long as he visits all cities during
// his trip and returns back to the origin. The salesman wants to keep travel
// costs low and minimize the total distance that he needs to travel. Implement
// an algorithm to return the optimal path he should take.
//
// Solution: The travelling salesman problem is quite difficult to solve, as it
// is an NP-hard problem. This means that even when it is broken down to smaller
// sub-problems, these will be at least as complex as the original problem. If
// N is the total number of cities under consideration, there are (N - 1)! / 2
// unique cycles the salesman can follow. Since the salesman travels in a circle
// the starting point does not really matter. From any starting city, there are
// N - 1 choices of cities to visit next, then N - 2 choices and so on. Thus the
// total number of permutations is (N - 1)!. This is finally divided by two to
// take into account reverse cycles, i.e. cycle ABCDA and ADCBA is actually the
// same.
//
// The implementation below uses a brute force approach to solve the problem by
// trying all possibilities. It uses a recursive algorithm that keeps track of
// nodes that have been visited and the distance up to now, updating the minimum
// distance and best bath accordingly. It contains an optimization to stop
// travelling down a path if the distance has already exceeded the minimum
// distance found previously. Nevertheless the runtime complexity of this
// approach is O(N!).

public class TravellingSalesman {

    // Holds the distances between cities.
    private static final class Distances {
        private final Map<String, Map<String, Double>> map = new HashMap<>();

        public void add(String from, String to, Double distance) {
            map.computeIfAbsent(from, (k) -> new HashMap<>());
            map.computeIfAbsent(to, (k) -> new HashMap<>());

            map.get(from).put(to, distance);
            map.get(to).put(from, distance);
        }

        public Double getDistance(String from, String to) {
            return map.get(from).get(to);
        }

        public List<String> getCities() {
            return new ArrayList<>(map.keySet());
        }
    }

    private static Double minDistance = Double.MAX_VALUE;
    private static List<String> minPath = new ArrayList<>();

    private static void travel(Distances distances,
                               Stack<String> visited,
                               Double distance) {

        // No point travelling further on this path.
        if (distance > minDistance) return;

        // Check if we have visited all cities.
        List<String> cities = distances.getCities();
        if (cities.size() == visited.size()) {
            if (distance < minDistance) {
                minDistance = distance;
                minPath = new ArrayList<>(visited);
            }
            return;
        }

        // Visit any cities that have not been visited.
        for (String nextCity : cities) {
            if (visited.search(nextCity) >= 0) continue;

            Double nextDistance = distance;
            if (visited.size() > 0) {
                nextDistance += distances.getDistance(visited.peek(), nextCity);
            }
            visited.push(nextCity);
            travel(distances, visited, nextDistance);
            visited.pop();
        }
    }

    // Distances between cities in the United Kingdom.
    private static final Distances UK = new Distances();
    static {
        UK.add("London", "Birmingham", 118.0);
        UK.add("London", "Leeds", 200.0);
        UK.add("London", "Sheffield", 167.0);
        UK.add("London", "Bradford", 207.0);
        UK.add("London", "Liverpool", 211.0);
        UK.add("London", "Manchester", 199.0);
        UK.add("London", "Bristol", 119.0);
        UK.add("Birmingham", "Leeds", 124.0);
        UK.add("Birmingham", "Sheffield", 90.0);
        UK.add("Birmingham", "Bradford", 129.0);
        UK.add("Birmingham", "Liverpool", 98.0);
        UK.add("Birmingham", "Manchester", 86.0);
        UK.add("Birmingham", "Bristol", 88.0);
        UK.add("Leeds", "Sheffield", 40.0);
        UK.add("Leeds", "Bradford", 10.0);
        UK.add("Leeds", "Liverpool", 72.0);
        UK.add("Leeds", "Manchester", 44.0);
        UK.add("Leeds", "Bristol", 208.0);
        UK.add("Sheffield", "Bradford", 48.0);
        UK.add("Sheffield", "Liverpool", 78.0);
        UK.add("Sheffield", "Manchester", 78.0);
        UK.add("Sheffield", "Bristol", 180.0);
        UK.add("Bradford", "Liverpool", 67.0);
        UK.add("Bradford", "Manchester", 39.0);
        UK.add("Bradford", "Bristol", 165.0);
        UK.add("Liverpool", "Manchester", 34.0);
        UK.add("Liverpool", "Bristol", 181.0);
        UK.add("Manchester", "Bristol", 168.0);
    }

    private static boolean testTravel() {
        minDistance = Double.MAX_VALUE;
        travel(UK, new Stack<String>(), 0.0);
        return 420 == minDistance &&
               8 == minPath.size() &&
               "Liverpool" == minPath.get(0) &&
               "Manchester" == minPath.get(1) &&
               "Bradford" == minPath.get(2) &&
               "Leeds" == minPath.get(3) &&
               "Sheffield" == minPath.get(4) &&
               "Birmingham" == minPath.get(5) &&
               "Bristol" == minPath.get(6) &&
               "London" == minPath.get(7);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testTravel()) {
            System.out.println("Travel test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

