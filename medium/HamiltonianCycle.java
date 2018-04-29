import java.util.Arrays;

// Task description: Given an undirected graph represented by its adjacency
// matrix, write a method to return whether there is a Hamiltonian Cycle and
// the list of nodes in the cycle. A Hamiltonian Cycle is a path that visits
// each vertex in the graph exactly once and the last vertex to be visited is
// connected to the first so that a cycle is formed.
//
// E.g. The graph on the left has a Hamiltonian cycle (0 => 1 => 2 => 4 => 3),
//      whereas the graph on the right does not.
//
//      (0)--(1)--(2)          (0)--(1)--(2)
//       |   / \   |            |   / \   |
//       |  /   \  |            |  /   \  |
//       | /     \ |            | /     \ |
//      (3)-------(4)           (3)      (4)
//
// Solution: Determining whether such a cycle exists in graphs is also called
// the Hamiltonian path problem, which is NP-complete. A brute force algorithm
// would be to generate all configurations of vertices and for each one check
// whether a cycle is formed. The runtime complexity of this solution would be
// O(n!) where n is the number of vertices, because there are a total of n!
// combinations. For the first position we have n vertices to choose from, for
// the second position n - 1, for the third position n - 2 and so on. Therefore
// the total number of combinations is n * (n - 1) * (n - 2) * ... = n!
//
// The implementation below uses a recursive approach with backtracking to find
// a Hamiltonian cycle more efficiently. We initially pick the first vertex as a
// starting point. Since we know that the cycle will pass through all vertices,
// it does not really matter which vertex we pick to start from. The algorithm
// then attempts to follow all edges of each vertex until a cycle has been
// identified, backtracking when necessary and immediately returning if a
// solution has been identified. If there is no cycle, the full solution space
// will be explored before returning null.

public class HamiltonianCycle {

    private static boolean find(int[][] matrix, int[] path, int index) {

        // If all nodes have been visited, check a complete cycle is formed.
        if (index == matrix.length) {
            return matrix[0][path[index - 1]] == 1;
        }

        // Follow all edges to vertices that have not been visited.
        // Backtrack and return as soon as a cycle has been identified.
        int current = path[index - 1];
        for (int next = 0; next < matrix[current].length; next++) {

            // Check there is an edge.
            if (matrix[current][next] == 0) continue;

            // Check the node has not been visited already.
            boolean visited = false;
            for (int i = 0; i < index; i++) {
                if (path[i] == next) {
                    visited = true;
                    break;
                }
            }
            if (visited) continue;

            path[index] = next;
            if (find(matrix, path, index + 1)) return true;
        }
        return false;
    }

    private static int[] find(int[][] matrix) {
        int[] path = new int[matrix.length];
        return find(matrix, path, 1) ? path : null;
    }

    private static boolean testCycle() {
        int[][] matrix = {{0, 1, 0, 1, 0},
                          {1, 0, 1, 1, 1},
                          {0, 1, 0, 0, 1},
                          {1, 1, 0, 0, 1},
                          {0, 1, 1, 1, 0}};

        return Arrays.equals(new int[] {0, 1, 2, 4, 3}, find(matrix));
    }

    private static boolean testNoCycle() {
        int[][] matrix = {{0, 1, 0, 1, 0},
                          {1, 0, 1, 1, 1},
                          {0, 1, 0, 0, 1},
                          {1, 1, 0, 0, 0},
                          {0, 1, 1, 0, 0}};

        return null == find(matrix);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testCycle()) {
            counter++;
            System.out.println("Cycle exists test failed!");
        }
        if (!testNoCycle()) {
            counter++;
            System.out.println("No cycle exists test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

