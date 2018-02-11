import static java.util.Arrays.asList;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;

// Task description: Given a map of cities and distances between them, implement
// an algorithm to return the shortest path between two given cities.
//
// Solution: The implementation below uses Dijkstra's algorithm to find the
// minimum distance from the start city to every other city in the graph. The
// algorithm uses a min-heap as a processing queue and initially adds the
// starting city into the queue. While the queue is not empty, we pick up and
// process the first item. If the city we are processing has been encountered
// before, it means that we have already visited it and thus can continue with
// the next item in the queue. If this is the first time we visit the city, it
// is guaranteed that the current route will be the shortest path, and this can
// be added to the results. If V is the number of vertices (cities) and E is the
// number of edges (paths) that connect two vertices, the runtime complexity of
// this algorithm is O(V * logV + E * logV). It takes O(logN) time to pop() or
// push() in the min-heap PriorityQueue. We need to do V pops and E pushes into
// the min-heap.

public class Dijkstra {

    // Path from one city to another and its distance.
    private static final class Path {
        private final String from;
        private final String to;
        private final double distance;

        public Path(String from, String to, double distance) {
            this.from = from;
            this.to = to;
            this.distance = distance;
        }

        public String getFrom() {
            return from;
        }

        public String getTo() {
            return to;
        }

        public double getDistance() {
            return distance;
        }
    }

    // A map of the area that contains paths between cities.
    private static final class AreaMap {
        private final Map<String, List<Path>> outbound = new HashMap<>();

        public void addPath(Path path) {
            outbound.computeIfAbsent(path.getFrom(), (k) -> new ArrayList<>());
            outbound.get(path.getFrom()).add(path);
        }

        public List<Path> getPathsFrom(String city) {
            outbound.computeIfAbsent(city, (k) -> new ArrayList<>());
            return outbound.get(city);
        }
    }

    // A route between cities and the total distance travelled.
    private static final class Route implements Comparable<Route> {
        private final List<String> cities;
        private final double totalDistance;

        public Route(List<String> cities, double totalDistance) {
            this.cities = cities;
            this.totalDistance = totalDistance;
        }

        public List<String> getCities() {
            return cities;
        }

        public double getTotalDistance() {
            return totalDistance;
        }

        public String getLastCity() {
            return cities.get(cities.size() - 1);
        }

        public Route move(String city, double distance) {
            List<String> newCities = new ArrayList<>();
            newCities.addAll(cities);
            newCities.add(city);

            double newDistance = totalDistance + distance;
            return new Route(newCities, newDistance);
        }

        public int compareTo(Route other) {
            double difference = this.totalDistance - other.totalDistance;
            return difference < 0 ? -1 : difference == 0 ? 0 : 1;
        }
    }

    private static Map<String, Route> optimalRoutes(String from, AreaMap area) {
        Map<String, Route> routes = new HashMap<>();
        Queue<Route> processing = new PriorityQueue<>();
        processing.add(new Route(asList(from), 0.0));

        while(!processing.isEmpty()) {
            Route route = processing.poll();
            String currentCity = route.getLastCity();

            if (routes.containsKey(currentCity)) continue;
            routes.put(currentCity, route);

            for (Path path : area.getPathsFrom(route.getLastCity())) {
                processing.add(route.move(path.getTo(), path.getDistance()));
            }
        }
        return routes;
    }

    private static final AreaMap UK = new AreaMap();
    static {
        UK.addPath(new Path("London", "Liverpool", 212));
        UK.addPath(new Path("London", "Manchester", 200));
        UK.addPath(new Path("Manchester", "Liverpool", 34));
        UK.addPath(new Path("Manchester", "Leeds", 44));
        UK.addPath(new Path("Leeds", "Sheffield", 36));
        UK.addPath(new Path("Manchester", "Sheffield", 37));
        UK.addPath(new Path("London", "Birmingham", 126));
        UK.addPath(new Path("Birmingham", "Liverpool", 99));
        UK.addPath(new Path("Birmingham", "Cardiff", 118));
        UK.addPath(new Path("Oxford", "Cardiff", 106));
        UK.addPath(new Path("London", "Oxford", 59));
    }

    private static boolean equal(Route route, double distance, String... cities) {
        if (route == null) return false;
        if (route.getTotalDistance() != distance) return false;

        List<String> routeCities = route.getCities();
        if (routeCities.size() != cities.length) return false;
        for (int i = 0; i < cities.length; i++) {
            if (!cities[i].equals(routeCities.get(i))) return false;
        }
        return true;
    }

    private static boolean testEmptyArea() {
        Map<String, Route> routes = optimalRoutes("London", new AreaMap());
        return 1 == routes.size() &&
               equal(routes.get("London"), 0.0, "London");
    }

    private static boolean testNoRoutes() {
        Map<String, Route> routes = optimalRoutes("Cardiff", UK);
        return 1 == routes.size() &&
               equal(routes.get("Cardiff"), 0.0, "Cardiff");
    }

    private static boolean testRoutes() {
        Map<String, Route> routes = optimalRoutes("London", UK);
        return 8 == routes.size() &&
               equal(routes.get("London"), 0.0, "London") &&
               equal(routes.get("Liverpool"), 212.0, "London", "Liverpool") &&
               equal(routes.get("Cardiff"), 165.0, "London", "Oxford", "Cardiff") &&
               equal(routes.get("Leeds"), 244.0, "London", "Manchester", "Leeds") &&
               equal(routes.get("Manchester"), 200.0, "London", "Manchester") &&
               equal(routes.get("Sheffield"), 237.0, "London", "Manchester", "Sheffield") &&
               equal(routes.get("Oxford"), 59.0, "London", "Oxford") &&
               equal(routes.get("Birmingham"), 126.0, "London", "Birmingham");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEmptyArea()) {
            System.out.println("Empty area test failed!");
            counter++;
        }
        if (!testNoRoutes()) {
            System.out.println("No routes test failed!");
            counter++;
        }
        if (!testRoutes()) {
            System.out.println("Routes test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

