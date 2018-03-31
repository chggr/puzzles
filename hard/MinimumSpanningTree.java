import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Set;

// Task description: Given an undirected graph with weighted edges, write a
// method to return the minimum spanning tree. This is a subset of the edges
// that connects all nodes together without any cycles and with the minimum
// possible total edge weight.
//
// Solution: The implementation below uses Prim's algorithm to find the minimum
// spanning tree of a weighted undirected graph. This is a greedy algorithm that
// maintains two sets of vertices: one set contains nodes already included in
// the MST and the other nodes that have not been included. At every step it
// considers all edges connecting the two sets and picks the edge with the
// minimum weight. This edge is added to the result and the node it points to
// is added to the set of nodes already included. This process is executed
// repeatedly until all nodes in the tree have been visited.
//
// In the implementation below, we start by picking up a node in the graph at
// random and adding it to the set of nodes that have been seen. We use a min
// heap to store the nodes edges. We then iterate until the full MST has been
// build, each time picking up the edge with the smallest weight from the queue.
// If the node it points to has already been seen, then the edge is ignored.
// Otherwise the edge is added to the MST and the node is added to the set of
// nodes that have already been seen. The runtime complexity of this algorithm
// is O(E * logE), where E is the number of edges in the graph. This is because
// we need in the worst case to insert and remove all edges in the min-heap.
// Each such operation takes logE and thus the total runtime complexity is
// O(E * logE);

public class MinimumSpanningTree {

    private static final class Edge implements Comparable<Edge> {
        int from, to, weight;

        public Edge(int from, int to, int weight) {
            this.from = from;
            this.to = to;
            this.weight = weight;
        }

        @Override
        public boolean equals(Object o) {
            if (!(o instanceof Edge)) return false;

            Edge other = (Edge) o;
            return this.from == other.from &&
                   this.to == other.to &&
                   this.weight == other.weight;
        }

        @Override
        public int hashCode() {
            int code = 17;
            code = code * 37 + from;
            code = code * 37 + to;
            code = code * 37 + weight;
            return code;
        }

        @Override
        public int compareTo(Edge other) {
            return this.weight - other.weight;
        }
    }

    private List<String> nodes = new ArrayList<>();
    private Map<Integer, Map<Integer, Edge>> edges = new HashMap<>();

    public void addNodes(String... names) {
        for (String name : names) {
            nodes.add(name);
        }
    }

    public void addEdge(int from, int to, int weight) {
        if (from >= nodes.size() || to >= nodes.size()) {
            throw new IllegalArgumentException("From or to node does not exist");
        }

        // Undirected graph.
        edges.computeIfAbsent(from, (k) -> new HashMap<>());
        edges.computeIfAbsent(to, (k) -> new HashMap<>());
        edges.get(from).put(to, new Edge(from, to, weight));
        edges.get(to).put(from, new Edge(to, from, weight));
    }

    public List<Edge> mst() {

        // Start with any node that has edges and populate min-heap.
        PriorityQueue<Edge> queue = new PriorityQueue<>();
        Set<Integer> seen = new HashSet<>();
        for (int i = 0; i < nodes.size(); i++) {
            Map<Integer, Edge> currEdges = edges.get(i);
            if (currEdges != null && !currEdges.isEmpty()) {
                queue.addAll(currEdges.values());
                seen.add(i);
                break;
            }
        }

        // Populate the MST by processing edges from min-heap.
        List<Edge> result = new ArrayList<>();
        while(!queue.isEmpty() && result.size() < nodes.size() - 1) {
            Edge current = queue.remove();
            if (seen.contains(current.to)) continue;

            result.add(current);
            seen.add(current.to);
            Map<Integer, Edge> currEdges = edges.get(current.to);
            if (currEdges != null && !currEdges.isEmpty()) {
                queue.addAll(currEdges.values());
            }
        }
        return result;
    }

    private static boolean testUnconnectedGraph() {
        MinimumSpanningTree mst = new MinimumSpanningTree();
        mst.addNodes("A", "B", "C", "D", "E");

        List<Edge> result = mst.mst();
        return result.isEmpty();
    }

    private static boolean testPositiveWeights() {
        MinimumSpanningTree mst = new MinimumSpanningTree();
        mst.addNodes("A", "B", "C", "D", "E");
        mst.addEdge(0, 3, 2);
        mst.addEdge(1, 2, 10);
        mst.addEdge(1, 3, 4);
        mst.addEdge(3, 4, 6);
        mst.addEdge(4, 1, 5);
        mst.addEdge(4, 2, 3);

        List<Edge> result = mst.mst();
        return 4 == result.size() &&
               result.contains(new Edge(0, 3, 2)) &&
               result.contains(new Edge(3, 1, 4)) &&
               result.contains(new Edge(1, 4, 5)) &&
               result.contains(new Edge(4, 2, 3));
    }

    private static boolean testNegativeWeights() {
        MinimumSpanningTree mst = new MinimumSpanningTree();
        mst.addNodes("A", "B", "C", "D", "E");
        mst.addEdge(0, 3, 2);
        mst.addEdge(1, 2, 10);
        mst.addEdge(1, 3, -2);
        mst.addEdge(3, 4, 6);
        mst.addEdge(4, 1, -1);
        mst.addEdge(4, 2, -3);

        List<Edge> result = mst.mst();
        return 4 == result.size() &&
               result.contains(new Edge(0, 3, 2)) &&
               result.contains(new Edge(3, 1, -2)) &&
               result.contains(new Edge(1, 4, -1)) &&
               result.contains(new Edge(4, 2, -3));
    }

    private static boolean testCycle() {
        MinimumSpanningTree mst = new MinimumSpanningTree();
        mst.addNodes("A", "B", "C", "D", "E");
        mst.addEdge(0, 1, 5);
        mst.addEdge(1, 2, 2);
        mst.addEdge(2, 3, 3);
        mst.addEdge(3, 4, 4);
        mst.addEdge(4, 0, 1);

        List<Edge> result = mst.mst();
        return 4 == result.size() &&
               result.contains(new Edge(0, 4, 1)) &&
               result.contains(new Edge(4, 3, 4)) &&
               result.contains(new Edge(3, 2, 3)) &&
               result.contains(new Edge(2, 1, 2));
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
        if (!testCycle()) {
            counter++;
            System.out.println("Cycle test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

