#include <iostream>
#include <list>
#include <string>
#include <vector>

// Task description: Given a list of tasks and the dependencies between them,
// design a graph to hold this information and an algorithm to identify the
// correct order in which the tasks need to be executed. Throw an exception if
// the dependencies between the tasks are such that there is no way to complete
// them.
//
// E.g. For tasks A, B, C, D, E and dependencies (A,B), (A,C), (A,D), (B,C),
//      (D,C), (C,E), (D,E) we can build the first graph below and the correct
//      sequence of task execution is: A => B => D => C => E.
//
//      For tasks A, B, C, D and dependencies (A,B), (B,C), (C,D), (D,A), (D,B)
//      we can build the second graph below, but there is no correct sequence
//      of task execution because there are cycles in the graph.
//
//              |-->B-->|                     |<-------------|
//              A------>C--->E                A--->B--->C--->D
//              |-->D-->|    |                     |<--------|
//                  |------->|
//
// Solution: In the implementation below, three classes have been defined: Task
// that holds task information, Edge that represents an dependency between two
// tasks and Graph that represents the whole task graph. Kahn's algorithm for
// topology sorting has been employed in order to identify the correct sequence
// of task execution. The algorithm starts by looking for tasks that have no
// dependencies at all, as these will be the first tasks to be executed. It
// subsequently completes them and moves on to its dependent tasks to identify
// if any of them can now be executed. This process continues iteratively until
// there are no further tasks that can be completed. The implementation below
// also checks for cyclical dependencies in the task graph and in this case
// raises an exception. The runtime complexity of this solution is O(N + M),
// where N is the number of tasks and M is the number of dependencies between
// them.

using namespace std;

class Task {

    private:
        string name;

    public:
        Task(string name) : name(name) { }
        string getName() const { return name; }
};

template <class T> class Edge {

    private:
        T* from;
        T* to;

    public:
        Edge(T* from, T* to) : from(from), to(to) { }
        T* getFrom() const { return from; }
        T* getTo() const { return to; }
};

template <class T> class Graph {

    private:
        vector<T*> nodes;
        vector< Edge<T> > edges;

    public:
        vector<T*> getNodes() const { return nodes; }
        vector< Edge<T> > getEdges() const { return edges; }
        void addNode(T* node) { nodes.push_back(node); }
        void addEdge(T* from, T* to) { edges.push_back(Edge<T>(from, to)); }
        void deleteEdge(T* from, T* to);
        vector<T*> getEdgesTo(T* to);
        vector<T*> getEdgesFrom(T* from);
};

template <class T> void Graph<T>::deleteEdge(T* from, T* to) {

    for (int i = 0; i < edges.size(); i++) {
        Edge<T> edge = edges.at(i);
        if (edge.getFrom() == from && edge.getTo() == to) {
            edges.erase(edges.begin() + i);
            i--;
        }
    }
}

template <class T> vector<T*> Graph<T>::getEdgesTo(T* to) {

    vector<T*> results;
    for (int i = 0; i < edges.size(); i++) {
        Edge<T> edge = edges.at(i);
        if (edge.getTo() == to) {
            results.push_back(edge.getFrom());
        }
    }
    return results;
}

template <class T> vector<T*> Graph<T>::getEdgesFrom(T* from) {

    vector<T*> results;
    for (int i = 0; i < edges.size(); i++) {
        Edge<T> edge = edges.at(i);
        if (edge.getFrom() == from) {
            results.push_back(edge.getTo());
        }
    }
    return results;
}

vector<Task*> order(Graph<Task> graph) {

    vector<Task*> result;
    list<Task*> to_process;

    // Identify tasks with no dependencies.
    vector<Task*> tasks = graph.getNodes();
    for (int i = 0; i < tasks.size(); i++) {
        if (graph.getEdgesTo(tasks.at(i)).empty()) {
            to_process.push_back(tasks.at(i));
        }
    }

    while(!to_process.empty()) {
        Task* current = to_process.front();
        to_process.pop_front();
        result.push_back(current);

        vector<Task*> dependants = graph.getEdgesFrom(current);
        for (int i = 0; i < dependants.size(); i++) {
            Task* dependant = dependants.at(i);
            graph.deleteEdge(current, dependant);
            if (graph.getEdgesTo(dependant).empty()) {
                to_process.push_back(dependant);
            }
        }
    }

    if (!graph.getEdges().empty()) {
        throw "Unable to order, graph contains cycles!";
    }
    return result;
}

bool test_order_no_cycles() {
    Task a("Task A");
    Task b("Task B");
    Task c("Task C");
    Task d("Task D");
    Task e("Task E");

    Graph<Task> graph;
    graph.addNode(&a);
    graph.addNode(&b);
    graph.addNode(&c);
    graph.addNode(&d);
    graph.addNode(&e);

    graph.addEdge(&a, &b);
    graph.addEdge(&a, &c);
    graph.addEdge(&a, &d);
    graph.addEdge(&c, &e);
    graph.addEdge(&b, &c);
    graph.addEdge(&d, &c);
    graph.addEdge(&d, &e);

    vector<Task*> result = order(graph);
    return 5 == result.size() &&
           &a == result.at(0) &&
           &b == result.at(1) &&
           &d == result.at(2) &&
           &c == result.at(3) &&
           &e == result.at(4);
}

bool test_order_with_cycles() {
    Task a("Task A");
    Task b("Task B");
    Task c("Task C");
    Task d("Task D");

    Graph<Task> graph;
    graph.addNode(&a);
    graph.addNode(&b);
    graph.addNode(&c);
    graph.addNode(&d);

    graph.addEdge(&a, &b);
    graph.addEdge(&b, &c);
    graph.addEdge(&c, &d);
    graph.addEdge(&d, &a);
    graph.addEdge(&d, &b);

    try {
        vector<Task*> result = order(graph);
        return false;
    } catch (const char* message) {
        return true;
    }
}

int main() {
    int counter = 0;
    if  (!test_order_no_cycles()) {
        cout << "Order without cycles test failed!" << endl;
        counter++;
    }
    if  (!test_order_with_cycles()) {
        cout << "Order with cycles test failed!" << endl;
        counter++;
    }
    cout << counter << " tests failed." << endl;
}

