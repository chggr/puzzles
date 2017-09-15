// Task description: Given the head of a singly linked list, implement a method
// to delete the element in the middle of the list. How would you delete a list
// element if you were given access only to that element and not the head?
//
// E.g. For list 1 => 2 => 3 => 4, the method should delete 2
//      For list 1 => 2 => 3 => 4 => 5, the method should delete 3
//
// Solution: The implementation below uses two pointers (current and runner) to
// identify the middle element of the list and delete it. The current pointer
// is always incremented by one, whereas the runner by two. Therefore when the
// runner reaches the end of the list, current will point to the middle element.
//
// The middle element is deleted by copying the data from the next node over to
// the current node and then deleting the next node. This elegant method of
// deleting a node by copying the next node on top of it and deleting next
// helps us avoid keeping a pointer to the previous node. Please note this
// method cannot be used to delete the last element of the list.

public class ListDeleteMiddleElement {

    private static final class Node {
        private int value;
        private Node next;

        public Node(int value) {
            this.value = value;
        }
    }

    private static void deleteMiddle(Node head) {
        if (head == null || head.next == null || head.next.next == null) {
            return;
        }

        Node current = head;
        Node runner = head;
        while (runner.next != null && runner.next.next != null) {
            runner = runner.next.next;
            current = current.next;
        }

        current.value = current.next.value;
        current.next = current.next.next;
    }

    private static boolean testDelete_NullHead() {
        deleteMiddle(null);
        return true;
    }

    private static boolean testDelete_OneElement() {
        Node head = new Node(1);
        deleteMiddle(head);
        return 1 == head.value;
    }

    private static boolean testDelete_TwoElements() {
        Node head = new Node(1);
        head.next = new Node(2);
        deleteMiddle(head);
        return 1 == head.value && 2 == head.next.value;
    }

    private static boolean testDelete_EvenElementCount() {
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);
        head.next.next.next = new Node(4);
        deleteMiddle(head);
        return 1 == head.value &&
               3 == head.next.value &&
               4 == head.next.next.value &&
               null == head.next.next.next; 
    }

    private static boolean testDelete_OddElementCount() {
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);
        head.next.next.next = new Node(4);
        head.next.next.next.next = new Node(5);
        deleteMiddle(head);
        return 1 == head.value &&
               2 == head.next.value &&
               4 == head.next.next.value &&
               5 == head.next.next.next.value &&
               null == head.next.next.next.next;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testDelete_NullHead()) {
            System.out.println("Null head delete test failed!");
            counter++;
        }
        if (!testDelete_OneElement()) {
            System.out.println("One element delete test failed!");
            counter++;
        }
        if (!testDelete_TwoElements()) {
            System.out.println("Two elements delete test failed!");
            counter++;
        }
        if (!testDelete_EvenElementCount()) {
            System.out.println("Even element count delete test failed!");
            counter++;
        }
        if (!testDelete_OddElementCount()) {
            System.out.println("Odd element count delete test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

