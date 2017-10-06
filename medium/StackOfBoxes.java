import java.util.Arrays;
import java.util.List;

// Task description: Given a list of boxes with certain widths, heights and
// lengths, write a method to calculate the maximum height if the boxes are
// stacked one on top of the other. The boxes cannot be rotated and can only
// be stacked on top of one another if each box in the stack is strictly
// smaller than the box below it.
//
// Solution: The solution below uses a recursive algorithm with memoization to
// calculate the height of the tallest stack of boxes. Memoization is required
// so that we do not repeat the same calculations. It is implemented by
// creating a map that maps each box with the height of the tallest stack that
// can be created having it as base.

public class StackOfBoxes {

    private static final class Box {
        final int width;
        final int length;
        final int height;

        public Box(int width, int length, int height) {
            this.width = width;
            this.length = length;
            this.height = height;
        }

        public int getWidth() {
            return width;
        }

        public int getLength() {
            return length;
        }

        public int getHeight() {
            return height;
        }
    }

    private static boolean canStack(Box bottom, Box top) {
        return top.getWidth() < bottom.getWidth() &&
               top.getLength() < bottom.getLength() &&
               top.getHeight() < bottom.getHeight();
    }

    private static int stack(List<Box> boxes, int bottomIndex, int[] map) {
        if (bottomIndex < boxes.size() && map[bottomIndex] > 0) {
            return map[bottomIndex];
        }

        Box bottom = boxes.get(bottomIndex);
        int maxHeight = 0;

        for (int i = 0; i < boxes.size(); i++) {
            if (canStack(bottom, boxes.get(i))) {
                int newHeight = stack(boxes, i, map);
                maxHeight = Math.max(maxHeight, newHeight);
            }
        }
        maxHeight += bottom.getHeight();
        map[bottomIndex] = maxHeight;
        return maxHeight;
    }

    private static int stack(List<Box> boxes) {
        int maxHeight = 0;
        int[] map = new int[boxes.size()];
        for (int i = 0; i < boxes.size(); i++) {
            maxHeight = Math.max(maxHeight, stack(boxes, i, map));
        }
        return maxHeight;
    }

    private static boolean testCanStack() {
        return !canStack(new Box(8, 4, 9), new Box(8, 3, 8)) &&
               !canStack(new Box(8, 4, 9), new Box(7, 4, 8)) &&
               !canStack(new Box(8, 4, 9), new Box(7, 3, 9)) &&
               canStack(new Box(8, 4, 9), new Box(7, 3, 8));
    }

    private static boolean testStack_Unstackable() {
        return 10 == stack(Arrays.asList(new Box(10, 9, 8),
                    new Box(10, 9, 7), new Box(8, 9, 10)));
    }

    private static boolean testStack() {
        return 6 == stack(Arrays.asList(new Box(1, 1, 1),
                    new Box(2, 2, 2), new Box(3, 3, 3)));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testCanStack()) {
            System.out.println("Can stack test failed.");
            counter++;
        }
        if (!testStack_Unstackable()) {
            System.out.println("Stack unstackable boxes test failed.");
            counter++;
        }
        if (!testStack()) {
            System.out.println("Stack boxes test failed.");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

