import java.util.HashSet;
import java.util.Set;

// Task description: Given the head to a singly linked list, write a method to
// detect whether the list contains loops. It should return the node at the
// beginning of the loop or null if no loop exists. Can this be done in O(1)
// space complexity and O(N) runtime complexity, where N is the number of
// unique elements in the list?
//
// E.g. For list  1 => 2 => 3 => 4  it should return 2.
//                     |_________|
//
// Solution: The first implementation below traverses the list one node at a
// time, using a HashSet to keep track of the nodes it has already visited.
// For each node, it checks whether it is already in the Set. If yes, then
// the node is the beginning of a loop. This implementation is O(N) space and
// runtime complexity, as it stores references to all nodes in memory.
//
// The second implementation achieves O(1) space complexity by not using any
// additional memory at all. It uses two pointers: a slow pointer that moves
// one element at a time and a fast pointer that moves two elements at a time.
// If the list does not contain a loop, the fast pointer will soon reach the
// end of the list, at which point the method returns null. On the contrary,
// if the list contains a loop, the pointers will eventually meet.
//
// In order to identify the beginning of the loop, please note the following:
// Let's assume that the list has a non-looped part of size K. When the slow
// pointer is at the beginning of the loop, it has already made K steps and
// the fast pointer has made 2 * K steps. At the same time the fast pointer is
// LOOP_SIZE - K steps behind the slow pointer. The fast pointer is approaching
// the slow pointer by 1 node in every iteration, thus the two pointers will
// eventually meet after LOOP_SIZE - K steps. When they meet, they will  both
// be K steps away from the beginning of the loop. Thefore, after they meet
// we reset one of the pointers to point to head and move both pointers one
// element at a time. The node that they will meet for a second time will be
// the beginning of the loop.

public class ListLoopDetection {

    private static final class Node {
        private int value;
        private Node next;

        public Node(int value) {
            this.value = value;
        }
    }

    private static Node detectLoop(Node head) {
        Set<Node> history = new HashSet<>();
        Node current = head;
        while (current != null) {
            if (history.contains(current)) break;
            history.add(current);
            current = current.next;
        }
        return current;
    }

    private static Node detectLoop2(Node head) {
        Node current = head;
        Node runner = head;

        while (runner != null && runner.next != null) {
            current = current.next;
            runner = runner.next.next;
            if (current == runner) break;
        }
        if (runner == null || runner.next == null) {
            return null;
        }

        runner = head;
        while (current != runner) {
            runner = runner.next;
            current = current.next;
        }
        return current;
    }

    private static boolean testDetectLoop_NullHead() {
        return null == detectLoop(null) &&
               null == detectLoop2(null);
    }

    private static boolean testDetectLoop() {
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);
        head.next.next.next = new Node(4);
        head.next.next.next.next = head.next;

        return head.next == detectLoop(head) &&
               head.next == detectLoop2(head);
    }

    private static boolean testDetectLoop_NoLoop() {
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);
        head.next.next.next = new Node(4);

        return null == detectLoop(head) &&
               null == detectLoop2(head);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testDetectLoop_NullHead()) {
            System.out.println("Detect loop with null head test failed!");
            counter++;
        }
        if (!testDetectLoop()) {
            System.out.println("Detect loop test failed!");
            counter++;
        }
        if (!testDetectLoop_NoLoop()) {
            System.out.println("Detect loop without loop test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

