import java.util.HashSet;
import java.util.Set;

// Task description: Write a program to simulate the Langton's ant two
// dimensional Turing machine. An ant is sitting on an infinite grid of black
// and white cells. At the beginning of the simulation, all cells are white and
// the ant is facing right. At each step, the ant moves as follows:
//
// 1) If the current cell is white, flip the color to black, turn 90 degrees
// clockwise and move one cell forward.
// 2) If the current cell is black, flip the color to white, turn 90 degrees
// anti-clockwise and move one cell forward.
//
// Your program should be able to simulate the first K moves and print the final
// grid. Discuss what is the best data structure to hold the grid.
//
// Solution: The challenge in this task is to pick the correct data structure to
// hold the infinite grid. The most straight forward solution is to use a fixed
// size two dimensional array. The requirement is to simulate only the first K
// moves of the ant. Therefore the ant can only move K cells in each direction
// and the fixed size array should have 2*K number of rows and 2*K number of
// columns. This approach would work but it is very wasteful. The ant is moving
// in circles so most of the array would be unused.
//
// A second approach would be to use a resizeable array that will dynamically
// allocate more space as soon as the ant reaches one of its boundaries. E.g.
// each time the ant hits an edge, we double the size of the grid in that
// dimension. This approach works very well, offering an amortized insertion
// cost of O(1). Unfortunately it still uses more space that strictly required
// and the logic around resizing the array in all four directions can be quite
// difficult to get right.
//
// The implementation below uses a HashSet to hold the cells in the array that
// are black. This allows us to store only the minimum required information to
// represent the grid. Moreover, we also need to keep the bottom left and top
// right cells with the maximum dimensions that the ant has visited in order to
// print the grid.

public class Ant {

    // Represents a cell in the grid.
    private static final class Cell {

        private final int x;
        private final int y;

        public Cell(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }

        public boolean equals(Object o) {
            if (o == this) return true;
            if (!(o instanceof Cell)) return false;

            final Cell other = (Cell) o;
            return this.x == other.x && this.y == other.y;
        }

        public int hashCode() {
            int code = 17;
            code = code * 31 + x;
            code = code * 31 + y;
            return code;
        }
    }

    // Represents the grid.
    private static final class Grid {

        private final Set<Cell> blacks = new HashSet<>();
        private Cell from = new Cell(0, 0);
        private Cell to = new Cell(0, 0);

        private void updateBoundaries(Cell cell) {
            if (cell.getX() > to.getX()) {
                to = new Cell(cell.getX(), to.getY());
            }
            if (cell.getX() < from.getX()) {
                from = new Cell(cell.getX(), from.getY());
            }
            if (cell.getY() > to.getY()) {
                to = new Cell(to.getX(), cell.getY());
            }
            if (cell.getY() < from.getY()) {
                from = new Cell(from.getX(), cell.getY());
            }
        }

        public char get(Cell cell) {
            updateBoundaries(cell);
            return blacks.contains(cell) ? 'B' : 'W';
        }

        public void flip(Cell cell) {
            updateBoundaries(cell);
            if (blacks.contains(cell)) {
                blacks.remove(cell);
            } else {
                blacks.add(cell);
            }
        }

        public void print() {
            for (int y = to.getY(); y >= from.getY(); y--) {
                for (int x = from.getX(); x <= to.getX(); x++) {
                    System.out.print(get(new Cell(x, y)) + " ");
                }
                System.out.println();
            }
        }
    }

    private static enum Direction { U, D, L, R };

    private final Grid grid = new Grid();
    private Cell current = new Cell(0, 0);
    private Direction direction = Direction.R;

    private Direction rotate(Direction direction, boolean clockwise) {
        switch (direction) {
            case U : return clockwise ? Direction.R : Direction.L;
            case R : return clockwise ? Direction.D : Direction.U;
            case D : return clockwise ? Direction.L : Direction.R;
            case L : return clockwise ? Direction.U : Direction.D;
            default: throw new IllegalArgumentException("Invalid direction");
        }
    }

    private Cell moveForward(Cell current) {
        switch(direction) {
            case U: return new Cell(current.getX(), current.getY() + 1);
            case D: return new Cell(current.getX(), current.getY() - 1);
            case R: return new Cell(current.getX() + 1, current.getY());
            case L: return new Cell(current.getX() - 1, current.getY());
            default: throw new IllegalArgumentException("Invalid direction");
        }
    }

    public void move() {
        char color = grid.get(current);
        grid.flip(current);
        direction = rotate(direction, color == 'W');
        current = moveForward(current);
    }

    public void printGrid() {
        grid.print();
    }

    public static void main(String[] args) {
        Ant ant = new Ant();
        for (int i = 0; i < 1000; i++) {
            ant.move();
        }
        ant.printGrid();
    }
}

