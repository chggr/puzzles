import java.util.HashSet;
import java.util.Set;

// Task description: Given the heads of two signly linked lists, write a method
// to detect whether they intersect and return the intersecting node. Nodes are
// considered the same if they have the same reference, not value. Is it
// possible to achieve this in O(1) space complexity and O(M + N) runtime
// complexity, where M and N are the lists' lengths?
//
// E.g. For lists  1 => 2 => 3 => | 
//                                4 => 0  it should return node 4.
//                      6 => 5 => |
//
// Solution: The first implementation below traverses the first list, adding
// all its elements into a HashSet. It subsequently goes through the second
// list, checking whether each node is already in the Set. It returns either
// the first common node identified or null. This simple solution has O(M)
// space complexity and O(M + N) runtime comlexity.
//
// The second implementation achieves O(1) space complexity by not using any
// additional space at all. It first runs through both lists to get their
// lengths and tails. It returns null if the tails are different, since in this
// case the lists do not intersect. It sets two pointers to the start of each
// list and advances only the longer list pointer by the difference in lengths.
// Finally it moves both pointers until they point to the same element, which
// is the intersect.

public class ListIntersection {

    private static final class Node {
        private final int value;
        private Node next;

        public Node(int value) {
            this.value = value;
        }
    }

    private static Node intersect(Node head1, Node head2) {
        Set<Node> nodes1 = new HashSet<>();

        Node current = head1;
        while (current != null) {
            nodes1.add(current);
            current = current.next;
        }

        current = head2;
        while (current != null) {
            if (nodes1.contains(current)) break;
            current = current.next;
        }
        return current;
    }

    private static Node intersect2(Node head1, Node head2) {
        Node tail1 = null;
        int length1 = 0;
        Node tail2 = null;
        int length2 = 0;

        Node current = head1;
        while (current != null) {
            length1++;
            tail1 = current;
            current = current.next;
        }

        current = head2;
        while (current != null) {
            length2++;
            tail2 = current;
            current = current.next;
        }

        // If tails are not the same, lists don't intersect.
        if (tail1 != tail2) {
            return null;
        }

        Node longList = length1 > length2 ? head1 : head2;
        Node shortList = longList == head1 ? head2 : head1;
        int diff = Math.abs(length1 - length2);

        Node currentLong = longList;
        Node currentShort = shortList;
        while (diff > 0) {
            currentLong = currentLong.next;
            diff--;
        }
        while (currentLong != currentShort) {
            currentLong = currentLong.next;
            currentShort = currentShort.next;
        }
        return currentLong;
    }

    private static boolean testIntersect_NullHeads() {
        return null == intersect(null, null) &&
               null == intersect2(null, null);
    }

    private static boolean testIntersect() {
        Node intersect = new Node(4);
        intersect.next = new Node(0);

        Node head1 = new Node(1);
        head1.next = new Node(2);
        head1.next.next = new Node(3);
        head1.next.next.next = intersect;

        Node head2 = new Node(6);
        head2.next = new Node(5);
        head2.next.next = intersect;

        return intersect == intersect(head1, head2) &&
               intersect == intersect2(head1, head2);
    }

    private static boolean testIntersect_SameLength() {
        Node intersect = new Node(4);
        intersect.next = new Node(0);

        Node head1 = new Node(1);
        head1.next = new Node(2);
        head1.next.next = new Node(3);
        head1.next.next.next = intersect;

        Node head2 = new Node(7);
        head2.next = new Node(6);
        head2.next.next = new Node(5);
        head2.next.next.next = intersect;

        return intersect == intersect(head1, head2) &&
               intersect == intersect2(head1, head2);
    }

    private static boolean testDontIntersect() {
        Node head1 = new Node(1);
        head1.next = new Node(2);
        head1.next.next = new Node(3);
        head1.next.next.next = new Node(4);

        Node head2 = new Node(6);
        head2.next = new Node(5);
        head2.next.next = new Node(4);

        return null == intersect(head1, head2) &&
               null == intersect2(head1, head2);
    }

    private static boolean testDontIntersect_SameLength() {
        Node head1 = new Node(1);
        head1.next = new Node(2);
        head1.next.next = new Node(3);
        head1.next.next.next = new Node(4);

        Node head2 = new Node(7);
        head2.next = new Node(6);
        head2.next.next = new Node(5);
        head2.next.next.next = new Node(4);

        return null == intersect(head1, head2) &&
               null == intersect2(head1, head2);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testIntersect_NullHeads()) {
            System.out.println("Intersect with null heads test failed!");
            counter++;
        }
        if (!testIntersect()) {
            System.out.println("Intersect test failed!");
            counter++;
        }
        if (!testIntersect_SameLength()) {
            System.out.println("Intersect same length test failed!");
            counter++;
        }
        if (!testDontIntersect()) {
            System.out.println("Don't intersect test failed!");
            counter++;
        }
        if (!testDontIntersect_SameLength()) {
            System.out.println("Don't intersect same length test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

