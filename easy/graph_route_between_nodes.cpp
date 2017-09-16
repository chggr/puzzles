#include <iostream>
#include <queue>
#include <set>
#include <vector>

// Task description: Given a directed graph, design an algorithm to detect
// whether there is a route between two nodes.
//
// E.g. In the first graph below the algorithm should identify a path between
//      nodes 1 and 5, whereas on the second graph not.
//
//              -----=>----
//              |         |
//         1 => 2 => 3 => 4 => 5           1 => 2 => 3 <= 4 => 5
//         |         |                     |         |
//         -----<=----                     -----<=----
// 
// Solution: This problem can be solved by simple graph traversal using one of
// two well established algorithms: Breadth First Search (BFS) or Depth First
// Search (DFS). For both algorithms we will need to keep track of the nodes
// that have already been visited in order to avoid infinite loops when there
// are cycles in the graph.
//
// Breadth First Seach explores all neighbours of each node before moving on to
// any of their children. The search expands widely through the graph and not
// deeply. This algorithm is preferred if we want to find the shortest path or
// any path between two nodes. The implementation of this algorithm is not
// recursive and uses a queue to store the next elements to be examined.
//
// Depth First Search explores each branch completely before moving on to the
// next branch. The search expands deeply into the graph instead of widely.
// This algorithm is preferred if we want to visit every node in the graph, as
// it is simpler to implement recursively.

class Node {

    private:
        int value;
        std::vector<Node*> edges;

    public:
        Node(int val) : value(val) { }
        int getValue() { return value; }
        void addEdge(Node* edge) { edges.push_back(edge); }
        std::vector<Node*> getEdges() { return edges; }
};

bool routeToNodeBFS(Node* start, Node* end) {
    std::set<Node*> visited;
    std::queue<Node*> queue;
    queue.push(start);

    while(!queue.empty()) {
        Node* current = queue.front();
        queue.pop();
        visited.insert(current);

        if (current == end) return true;
        std::vector<Node*> edges = current->getEdges();
        for (int i = 0; i < edges.size(); i++) {
            if (visited.count(edges.at(i)) == 0) {
                queue.push(edges.at(i));
            }
        }
    }
    return false;
}

bool searchDFS(Node* start, Node* end, std::set<Node*> &visited) {
    if (start == end) return true;
    if (visited.count(start) != 0) return false;
    visited.insert(start);

    std::vector<Node*> edges = start->getEdges();
    for (int i = 0; i < edges.size(); i++) {
        if (searchDFS(edges.at(i), end, visited)) {
            return true;
        }
    }
    return false;
}

bool routeToNodeDFS(Node* start, Node* end) {
    std::set<Node*> visited;
    return searchDFS(start, end, visited);
}

bool test_no_route_no_loops() {
    Node node1(1);
    Node node2(2);
    Node node3(3);

    node1.addEdge(&node2);

    return !routeToNodeBFS(&node1, &node3) &&
           !routeToNodeDFS(&node1, &node3);
}

bool test_no_route_with_loops() {
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);

    node1.addEdge(&node2);
    node2.addEdge(&node3);
    node3.addEdge(&node1);
    node4.addEdge(&node3);
    node4.addEdge(&node5);

    return !routeToNodeBFS(&node1, &node5) &&
           !routeToNodeDFS(&node1, &node5);
}

bool test_route_no_loops() {
    Node node1(1);
    Node node2(2);
    Node node3(3);

    node1.addEdge(&node2);
    node2.addEdge(&node3);

    return routeToNodeBFS(&node1, &node3) &&
           routeToNodeDFS(&node1, &node3);
}

bool test_route_with_loops() {
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);

    node1.addEdge(&node2);
    node2.addEdge(&node3);
    node2.addEdge(&node4);
    node3.addEdge(&node1);
    node3.addEdge(&node4);
    node4.addEdge(&node5);

    return routeToNodeBFS(&node1, &node5) &&
           routeToNodeDFS(&node1, &node5);
}

int main() {
    int counter = 0;
    if (!test_no_route_no_loops()) {
        std::cout << "No route without loops test failed!" << std::endl;
        counter++;
    }
    if (!test_no_route_with_loops()) {
        std::cout << "No route with loops test failed!" << std::endl;
        counter++;
    }
    if (!test_route_no_loops()) {
        std::cout << "Route without loops test failed!" << std::endl;
        counter++;
    }
    if (!test_route_with_loops()) {
        std::cout << "Route with loops test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

