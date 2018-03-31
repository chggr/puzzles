import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: Given a graph with edges that can have both positive and
// negative weights, write a method to calculate the shortest distance from a
// start node to all other nodes in the graph.
//
// Solution: The implementation below is using the Bellman-Ford algorithm to
// compute the shortest path from the start node to all other nodes in the graph.
// This algorithm is slower that Dijkstra's algorithm, but the latter cannot
// handle negative edge weights. Please note that if the graph contains a
// negative cycle, i.e. a cycle whose edges sum to a negative value, that is
// reachable from the start node, then there is no cheapest path. This algorithm
// can detect negative cycles and report their existence.
//
// The Bellman-Ford algorithm is based on the principle of relaxation, in which
// an approximation to the correct distance is gradually replaced by a more
// accurate value until eventually reaching the best solution. In contrast to
// Dijkstra's algorithm, which uses a priority queue to greedily select the
// closest nodes that have not been processed and performs this relaxation
// process in all of its outgoing edges, the Bellman-Ford algorithm relaxes all
// of the edges at the same time. It repeats this process a total of V - 1 times
// where V is the total number of nodes / vertices in the graph. In each of
// these repetitions, the number of nodes with correctly calculated distances
// grows until eventually all nodes have the correct distance from start.
//
// In the implementation below we first create an output array to contain the
// minimum distances from the starting node to each other node. The algorithm
// initializes the distance to zero for the source and to Integer.MAX_VALUE for
// all other nodes. Then it iterates a maximum of V times, where V is the number
// of nodes in the graph, and in each iteration it checks whether the array can
// be updated with smaller values. The loop ends prematurely if the algorithm
// detects that no work has been done during the last iteration. The runtime
// complexity of this algorithm is O(V * E), where V is the number of vertices
// and E is the number of edges.

public class BellmanFord {

    private List<String> nodes = new ArrayList<>();
    private Map<Integer, Map<Integer, Integer>> edges = new HashMap<>();

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

    public List<Integer> shortestPath(int from) {

        // Initialize the shortest paths list.
        List<Integer> result = new ArrayList<>();
        for (String node : nodes) {
            result.add(Integer.MAX_VALUE);
        }
        result.set(from, 0);

        // Populate the shortest paths until no work has been done
        // or we reach a maximum of V iterations (V is number of nodes).
        boolean hasDoneWork = true;
        int counter = nodes.size();
        while (hasDoneWork && counter > 0) {
            hasDoneWork = false;
            counter--;

            for (int i = 0; i < result.size(); i++) {
                Integer dist = result.get(i);
                if (dist.equals(Integer.MAX_VALUE)) continue;

                Map<Integer, Integer> currEdges = edges.get(i);
                if (currEdges == null || currEdges.isEmpty()) continue;

                for (Map.Entry<Integer, Integer> edge : currEdges.entrySet()) {
                    int newDist = dist + edge.getValue();
                    if (newDist < result.get(edge.getKey())) {
                        hasDoneWork = true;
                        result.set(edge.getKey(), newDist);
                    }
                }
            }
        }
        return result;
    }

    private static boolean testUnconnectedGraph() {
        BellmanFord bf = new BellmanFord();
        bf.addNodes("A", "B", "C", "D", "E");

        List<Integer> result = bf.shortestPath(0);
        return result.equals(Arrays.asList(0, Integer.MAX_VALUE,
                    Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE));
    }

    private static boolean testPositiveWeights() {
        BellmanFord bf = new BellmanFord();
        bf.addNodes("A", "B", "C", "D", "E");
        bf.addEdge(0, 3, 2);
        bf.addEdge(1, 2, 10);
        bf.addEdge(1, 3, 4);
        bf.addEdge(3, 4, 6);
        bf.addEdge(4, 1, 5);

        List<Integer> result = bf.shortestPath(0);
        return result.equals(Arrays.asList(0, 13, 23, 2, 8));
    }

    private static boolean testNegativeWeights() {
        BellmanFord bf = new BellmanFord();
        bf.addNodes("A", "B", "C", "D", "E");
        bf.addEdge(0, 3, 2);
        bf.addEdge(1, 2, 10);
        bf.addEdge(1, 3, -2);
        bf.addEdge(3, 4, 6);
        bf.addEdge(4, 1, -1);

        List<Integer> result = bf.shortestPath(0);
        return result.equals(Arrays.asList(0, 7, 17, 2, 8));
    }

    private static boolean testNegativeCycle() {
        BellmanFord bf = new BellmanFord();
        bf.addNodes("A", "B", "C", "D", "E");
        bf.addEdge(0, 1, 2);
        bf.addEdge(1, 2, -1);
        bf.addEdge(2, 3, -2);
        bf.addEdge(3, 1, -3);
        bf.addEdge(2, 4, 5);

        List<Integer> result = bf.shortestPath(0);
        return result.equals(Arrays.asList(0, -28, -23, -25, -18));
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
        if (!testNegativeCycle()) {
            counter++;
            System.out.println("Negative cycle test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

