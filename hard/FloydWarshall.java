import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: Given a graph with edges that have positive or negative
// weights, write a method to compute the shortest distance and path between
// any start and end node in the graph. The graph is guaranteed not to have any
// negative cycles, i.e. cycles where all edges have negative weights.
//
// Solution: The implementation below is using the Floyd-Warshall algorithm to
// compute the shortest distance and path between any two nodes in the given
// graph. This algorithm uses a dynamic programming approach to arrive to the
// result and its overall runtime complexity is O(N^3), where N is the number of
// nodes in the graph. The space complexity is O(N^2) for the two arrays that
// memoize the shortest distance and path from any node to any other node.
//
// At the beginning we initialize two NxN arrays, dist and path, that will hold
// the minimum distance and path respectively. All positions in the path array
// are initially set to -1 and all positions on the distance array are set to
// Integer.MAX_VALUE except from positions on the diagonal that are set to 0.
// This is because the shortest distance is zero when the start and end nodes
// are the same. We then go through all edges in the graph and add information
// to both path and dist arrays. Finally, a triple for loop is used to test
// every combination of edges and incrementally improve the values in arrays
// dist and path until the shortest distances between nodes are found. The
// outer loop goes through all nodes in the graph and for all start and end
// nodes checks whether that node would be part of the shortest path between
// start and end. This process effectively goes through all nodes one by one
// and updates all shortest paths to include the picked node as an intermediate
// if necessary.

public class FloydWarshall {

    private List<String> nodes = new ArrayList<>();
    private Map<Integer, Map<Integer, Integer>> edges = new HashMap<>();
    private int[][] dist = null;
    private int[][] path = null;

    public void addNodes(String... names) {
        for (String name : names) {
            nodes.add(name);
        }
    }

    public void addEdge(int from, int to, int weight) {
        if (from >= nodes.size() || to >= nodes.size()) {
            throw new IllegalArgumentException("From or to node does not exist");
        }

        edges.computeIfAbsent(from, (k) -> new HashMap<>());
        edges.get(from).put(to, weight);
    }

    public void compute() {
        int N = nodes.size();

        // Initialize distances and paths.
        dist = new int[N][N];
        path = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist[i][j] = (i == j ? 0 : Integer.MAX_VALUE);
                path[i][j] = -1;
            }
        }

        // Add edges information to distances and paths.
        for (Integer from : edges.keySet()) {
            for (Integer to : edges.get(from).keySet()) {
                dist[from][to] = edges.get(from).get(to);
                path[from][to] = to;
            }
        }

        // Check if going through an intermediate node is faster.
        for (int i = 0; i < N; i++) {
            for (int from = 0; from < N; from++) {
                for (int to = 0; to < N; to++) {
                    if (dist[from][i] == Integer.MAX_VALUE) continue;
                    if (dist[i][to] == Integer.MAX_VALUE) continue;

                    if (dist[from][to] > dist[from][i] + dist[i][to]) {
                        dist[from][to] = dist[from][i] + dist[i][to];
                        path[from][to] = path[from][i];
                    }
                }
            }
        }
    }

    public int shortestDistance(int from, int to) {
        return dist[from][to];
    }

    public List<Integer> shortestPath(int from, int to) {
        List<Integer> result = new ArrayList<>();
        result.add(from);
        while (path[from][to] != -1) {
            result.add(path[from][to]);
            from = path[from][to];
        }
        return result;
    }

    private static boolean testUnconnectedGraph() {
        FloydWarshall fw = new FloydWarshall();
        fw.addNodes("A", "B", "C", "D", "E");
        fw.compute();

        List<Integer> path = fw.shortestPath(0, 4);
        int distance = fw.shortestDistance(0, 4);
        return Integer.MAX_VALUE == distance &&
               Arrays.asList(0).equals(path);
    }

    private static boolean testPositiveWeights() {
        FloydWarshall fw = new FloydWarshall();
        fw.addNodes("A", "B", "C", "D", "E");
        fw.addEdge(0, 3, 2);
        fw.addEdge(1, 2, 10);
        fw.addEdge(1, 3, 4);
        fw.addEdge(3, 4, 6);
        fw.addEdge(4, 1, 5);
        fw.compute();

        List<Integer> path = fw.shortestPath(0, 4);
        int distance = fw.shortestDistance(0, 4);
        return 8 == distance &&
               Arrays.asList(0, 3, 4).equals(path);
    }

    private static boolean testNegativeWeights() {
        FloydWarshall fw = new FloydWarshall();
        fw.addNodes("A", "B", "C", "D", "E");
        fw.addEdge(0, 3, 2);
        fw.addEdge(1, 2, 10);
        fw.addEdge(1, 3, -2);
        fw.addEdge(3, 4, 6);
        fw.addEdge(4, 1, -1);
        fw.compute();

        List<Integer> path = fw.shortestPath(0, 2);
        int distance = fw.shortestDistance(0, 2);
        return 17 == distance &&
               Arrays.asList(0, 3, 4, 1, 2).equals(path);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testUnconnectedGraph()) {
            counter++;
            System.out.println("Unconnected graph test failed!");
        }
        if (!testPositiveWeights()) {
            counter++;
            System.out.println("Positive weights test failed!");
        }
        if (!testNegativeWeights()) {
            counter++;
            System.out.println("Negative weights test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

