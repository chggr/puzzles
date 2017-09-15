// Task description: Given the head to a singly linked list, implement a method
// to check if the list is a palindrome.
//
// E.g. For list 1 => 2 => 2 => 2 => 1, it should return true
//      For list 1 => 2 => 3 => 4 => 5, it should return false
//
// Solution: The first implementation below creates a new list that contains
// all elements in the original list but in reverse order. The two lists are
// subsequently compared for equality. Strictly speaking only the first half
// of each list needs to be compared, as it is certain the second part is
// going to be equal.
//
// The second implementation iterates through the given list with a slow and a
// fast pointer. The slow pointer moves one element at a time and the element
// it points to is pushed into a stack. The fast pointer moves two elements at
// a time. When the fast pointer reaches the end of the list, the slow pointer
// will still be at the middle. We continue moving the slow pointer in the
// second part of the list, popping elements from the stack and checking
// whether they appear in the second part of the list.

public class ListPalindrome {

    private static final class Node {
        private final int value;
        private Node next;

        public Node(int value) {
            this.value = value;
        }
    }

    private static boolean isPalindrome(Node head) {
        return head != null && areListsEqual(head, reverseList(head));
    }

    private static Node reverseList(Node head) {
        Node newHead = null;
        Node current = head;

        while (current != null) {
            Node node = new Node(current.value);
            node.next = newHead;
            newHead = node;
            current = current.next;
        }
        return newHead;
    }

    private static boolean areListsEqual(Node head1, Node head2) {
        while (head1 != null && head2 != null) {
            if (head1.value != head2.value) {
                return false;
            }
            head1 = head1.next;
            head2 = head2.next;
        }
        return head1 == null && head2 == null;
    }

    private static boolean isPalindrome2(Node head) {
        Node stack = null;
        Node current = head;
        Node runner = head;

        while (runner != null && runner.next != null) {
            Node node = new Node(current.value);
            node.next = stack;
            stack = node;

            current = current.next;
            runner = runner.next.next;
        }

        // For lists with odd number of elements.
        if (runner != null) {
            current = current.next;
        }
        return head != null && areListsEqual(current, stack);
    }

    private static boolean testIsPalindrome_NullHead() {
        return !isPalindrome(null) && !isPalindrome2(null);
    }

    private static boolean testIsPalindrome_OneElement() {
        Node node = new Node(1);
        return isPalindrome(node) && isPalindrome2(node);
    }

    private static boolean testIsPalindrome_EvenElements() {
        Node head1 = new Node(0);
        head1.next = new Node(1);
        head1.next.next = new Node(1);
        head1.next.next.next = new Node(0);

        Node head2 = new Node(0);
        head2.next = new Node(1);
        head2.next.next = new Node(2);
        head2.next.next.next = new Node(3);

        return isPalindrome(head1) && !isPalindrome(head2) &&
               isPalindrome2(head1) && !isPalindrome2(head2);
    }

    private static boolean testIsPalindrome_OddElements() {
        Node head1 = new Node(0);
        head1.next = new Node(1);
        head1.next.next = new Node(2);
        head1.next.next.next = new Node(1);
        head1.next.next.next.next = new Node(0);

        Node head2 = new Node(0);
        head2.next = new Node(1);
        head2.next.next = new Node(2);
        head2.next.next.next = new Node(1);
        head2.next.next.next.next = new Node(2);

        return isPalindrome(head1) && !isPalindrome(head2) &&
               isPalindrome2(head1) && !isPalindrome2(head2);
    }

    private static boolean testIsPalindrome_Duplicates() {
        Node head1 = new Node(0);
        head1.next = new Node(1);
        head1.next.next = new Node(1);
        head1.next.next.next = new Node(2);
        head1.next.next.next.next = new Node(2);
        head1.next.next.next.next = new Node(0);

        Node head2 = new Node(0);
        head2.next = new Node(0);
        head2.next.next = new Node(0);
        head2.next.next.next = new Node(0);
        return !isPalindrome(head1) && isPalindrome(head2) &&
               !isPalindrome2(head1) && isPalindrome2(head2);
    }

    public static void main(String args[]) {
        int counter = 0;
        if (!testIsPalindrome_NullHead()) {
            System.out.println("Is palindrome test with null head failed!");
            counter++;
        }
        if (!testIsPalindrome_OneElement()) {
            System.out.println("Is palindrome test with one element failed!");
            counter++;
        }
        if (!testIsPalindrome_EvenElements()) {
            System.out.println("Is palindrome test with even elements failed!");
            counter++;
        }
        if (!testIsPalindrome_OddElements()) {
            System.out.println("Is palindrome test with odd elements failed!");
            counter++;
        }
        if (!testIsPalindrome_Duplicates()) {
            System.out.println("Is palindrome test with duplicates failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

