#include <iostream>
#include <queue>

// Task description: Given an empty chessboard (8 x 8 grid), a knight is placed
// at a given position (x, y). Write a method to calculate the probability of
// the knight staying at the board after a given number of moves. The knight's
// possible moves are shown in the board bellow. Once the knight has fallen off
// the board, it cannot reenter.
//
//    * * * * * * * *
//    * * * * * * * *
//    * * X * X * * *
//    * X * * * X * *
//    * * * K * * * *
//    * X * * * X * *
//    * * X * X * * *
//    * * * * * * * *
//
// Solution: The first implementation below uses Depth First Search (DFS) to
// calculate the probability of the knight staying on the board. A recursive
// method has been defined to evaluate each move. If there are no moves left,
// the counters are incremented according to whether the current or any previous
// moves has led the knight to fall off the board. On the contrary, if there are
// moves left, the method calls itself recursively to evaluate each one of the
// eight new moves. If n is the given number of moves, the runtime complexity of
// this solution is O(8 ^ n), because at each recursion we need to further
// examine eight possible moves. The space complexity is O(n), because at any
// given point in time the method will have recursed up to n times. This
// implementation can be converted from recursive to iterative by using a stack.
//
// The second implementation uses Breadth First Search (BFS) to solve the task.
// A queue is used to store the moves under consideration. The algorithm removes
// the first item in the queue until the queue is empty. For each item, it checks
// whether there are any moves left. If yes, then new moves are created and put
// in the queue. If not, the counters are incremented according to whether the
// move under consideration or any previous move before it has left the knight
// to fall off the board. The runtime complexity of this approach is O(8 ^ n),
// because for every move up to eight other moves are added to the queue. The
// space complexity is also O(8 ^ n), because as we reach the nth level the
// queue will contain 8 ^ n moves to evaluate.

int in = 0;
int out = 0;

void move(int x, int y, int left, bool alive) {

    // Must already be alive and onto the board.
    alive = alive && x >= 0 && y >= 0 && x < 8 && y < 8;

    // No more moves left, increment counts.
    if (left == 0) {
        if (alive) in++;
        else out++;
        return;
    }

    // Move towards all possible directions.
    move(x + 2, y - 1, left - 1, alive);
    move(x + 2, y + 1, left - 1, alive);
    move(x - 2, y - 1, left - 1, alive);
    move(x - 2, y + 1, left - 1, alive);
    move(x + 1, y - 2, left - 1, alive);
    move(x - 1, y - 2, left - 1, alive);
    move(x + 1, y + 2, left - 1, alive);
    move(x - 1, y + 2, left - 1, alive);
}

double probability_dfs(int x, int y, int left) {
    in = 0;
    out = 0;
    move(x, y, left, true);
    return (in * 1.0) / (out + in);
}

class Move {

    private:
        int x;
        int y;
        int left;
        bool alive;

    public:
        Move(int x, int y, int left, bool alive) :
            x(x), y(y), left(left), alive(alive) { }
        int getX() { return x; }
        int getY() { return y; }
        int getLeft() { return left; }
        bool isAlive() { return alive && x >= 0 && y >= 0 && x < 8 && y < 8; }
};

double probability_bfs(int x, int y, int left) {
    int in = 0;
    int out = 0;

    // Queue holds the moves to be evaluated.
    std::queue<Move> moves;
    moves.push(Move(x, y, left, true));

    while (!moves.empty()) {
        Move move = moves.front();
        moves.pop();
        int left = move.getLeft();

        // If no more moves left, increment the stats.
        if (left == 0) {
            if (move.isAlive()) in++;
            else out++;
            continue;
        }

        int x = move.getX();
        int y = move.getY();
        bool alive = move.isAlive();
        moves.push(Move(x + 2, y - 1, left - 1, alive));
        moves.push(Move(x + 2, y + 1, left - 1, alive));
        moves.push(Move(x - 2, y - 1, left - 1, alive));
        moves.push(Move(x - 2, y + 1, left - 1, alive));
        moves.push(Move(x + 1, y + 2, left - 1, alive));
        moves.push(Move(x - 1, y + 2, left - 1, alive));
        moves.push(Move(x + 1, y - 2, left - 1, alive));
        moves.push(Move(x - 1, y - 2, left - 1, alive));
    }

    return (in * 1.0) / (in + out);
}

bool test_out() {
    return 0.0 == probability_dfs(-1, -2, 1) &&
           0.0 == probability_bfs(-1, -2, 1);
}

bool test_corner() {
    return 0.25 == probability_dfs(0, 0, 1) &&
           0.25 == probability_dfs(7, 0, 1) &&
           0.25 == probability_dfs(0, 7, 1) &&
           0.25 == probability_dfs(7, 7, 1) &&
           0.25 == probability_bfs(0, 0, 1) &&
           0.25 == probability_bfs(7, 0, 1) &&
           0.25 == probability_bfs(0, 7, 1) &&
           0.25 == probability_bfs(7, 7, 1);
}

bool test_side() {
    return 0.5 == probability_dfs(4, 0, 1) &&
           0.5 == probability_dfs(0, 4, 1) &&
           0.5 == probability_dfs(7, 4, 1) &&
           0.5 == probability_dfs(4, 7, 1) &&
           0.5 == probability_bfs(4, 0, 1) &&
           0.5 == probability_bfs(0, 4, 1) &&
           0.5 == probability_bfs(7, 4, 1) &&
           0.5 == probability_bfs(4, 7, 1);
}

bool test_in() {
    return 1.0 == probability_dfs(4, 4, 1) &&
           0.875 == probability_dfs(4, 4, 2) &&
           1.0 == probability_bfs(4, 4, 1) &&
           0.875 == probability_bfs(4, 4, 2);
}

int main() {
    int counter = 0;
    if (!test_out()) {
        std::cout << "Out test failed!" << std::endl;
        counter++;
    }
    if (!test_corner()) {
        std::cout << "Corner test failed!" << std::endl;
        counter++;
    }
    if (!test_side()) {
        std::cout << "Side test failed!" << std::endl;
        counter++;
    }
    if (!test_in()) {
        std::cout << "In test failed!" << std::endl;
        counter++;
    }
    std::cout << counter << " tests failed." << std::endl;
}

