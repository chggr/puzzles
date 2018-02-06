import java.util.HashMap;
import java.util.Map;

// Task description: Design and build a "Least Recently Used" (LRU) cache, which
// evicts the least recently used item once it reaches its maximum capacity. The
// cache should be able to map keys and implement an interface similar to a Map.
// Its maximum capacity will be provided during construction.
//
// Solution: Since the LRU cache will need to implement an interface similar to
// Map, it makes sense to use a HashMap as the underlying data structure. This
// will allow us to store and retrieve key value pairs. Unfortunately a HashMap
// does not provide an easy way to detect which is the least recently used item
// to be removed. We could add a timestamp to each item to track the last time
// it was used, but we would still need to iterate through all elements of the
// map to identify the least recently used. This approach would offer O(1) to
// get an element but O(N) to remove the least recently used element.
//
// Instead we could use a linked list to order items from most to least recently
// used. When the list reaches maximum capacity,we can simply remove the element
// at the tail. Unfortunately a linked list does not provide an easy way to get
// an item, as we would need to iterate through the whole list to retrieve it.
// This approach would offer O(N) to get an element but O(1) to remove the least
// recently used element.
//
// The implementation below uses both approaches and to achieve O(1) runtime
// complexity both when retrieving an element and when removing the least
// recently used element. The underlying data structure is a HashMap, whose
// elements are also part of a doubly linked list. The map guarantees fast
// access to each key-value pair and the list guarantees fast access to the
// least recently used element.

public class LRUCache {

    private static final class Cache<K, V> {

        private static final class Node<K, V> {
            Node<K, V> next;
            Node<K, V> previous;
            K key;
            V value;

            public Node(K key, V value) {
                this.key = key;
                this.value = value;
            }
        }

        private Map<K, Node<K, V>> map;
        private Node<K, V> head;
        private Node<K, V> tail;
        private int capacity;

        public Cache(int capacity) {
            this.capacity = capacity;
            this.map = new HashMap<>(capacity);
        }

        public void put(K key, V value) {
            Node<K, V> node = map.get(key);
            if (node == null) {
                node = new Node<>(key, value);
                map.put(key, node);
            } else {
                node.value = value;
                listRemove(node);
            }
            listInsertHead(node);

            while (map.size() > capacity) {
                map.remove(tail.key);
                listRemove(tail);
            }
        }

        public V get(K key) {
            Node<K, V> node = map.get(key);
            if (node == null) return null;

            if (node != head) {
                listRemove(node);
                listInsertHead(node);
            }
            return node.value;
        }

        public void remove(K key) {
            Node<K, V> node = map.get(key);
            map.remove(key);
            listRemove(node);
        }

        public int size() {
            return map.size();
        }

        private void listRemove(Node<K, V> node) {
            if (node == null) return;

            if (node.previous != null) node.previous.next = node.next;
            if (node.next != null) node.next.previous = node.previous;
            if (node == head) head = node.next;
            if (node == tail) tail = node.previous;
        }

        private void listInsertHead(Node<K, V> node) {
            if (node == null) return;

            if (head == null) {
                tail = node;
            } else {
                head.previous = node;
                node.next = head;
                node.previous = null;
            }
            head = node;
        }
    }

    private static boolean testPut_CapacityExceeded() {
        Cache<Integer, String> cache = new Cache<>(2);
        cache.put(1, "one");
        cache.put(2, "two");
        cache.put(3, "three");

        return cache.get(1) == null &&
               cache.get(2) == "two" &&
               cache.get(3) == "three" &&
               cache.size() == 2;
    }

    private static boolean testPut_CapacityNotExceeded() {
        Cache<Integer, String> cache = new Cache<>(2);
        cache.put(1, "one");
        cache.put(2, "two");

        return cache.get(1) == "one" &&
               cache.get(2) == "two" &&
               cache.size() == 2;
    }

    private static boolean testPut_SameKey() {
        Cache<Integer, String> cache = new Cache<>(2);
        cache.put(1, "one");
        cache.put(2, "two");
        cache.put(1, "one");
        cache.put(3, "three");

        return cache.get(1) == "one" &&
               cache.get(2) == null &&
               cache.get(3) == "three" &&
               cache.size() == 2;
    }


    private static boolean testGet_CapacityExceeded() {
        Cache<Integer, String> cache = new Cache<>(2);
        cache.put(1, "one");
        cache.put(2, "two");
        cache.get(1);
        cache.put(3, "three");

        return cache.get(1) == "one" &&
               cache.get(2) == null &&
               cache.get(3) == "three" &&
               cache.size() == 2;
    }

    private static boolean testRemove() {
        Cache<Integer, String> cache = new Cache<>(2);
        cache.put(1, "one");
        cache.put(2, "two");
        cache.put(3, "three");
        cache.remove(1);
        cache.remove(2);
        cache.remove(3);

        return cache.get(1) == null &&
               cache.get(2) == null &&
               cache.get(3) == null &&
               cache.size() == 0;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testPut_CapacityExceeded()) {
            System.out.println("Put capacity exceeded test failed!");
            counter++;
        }
        if (!testPut_CapacityNotExceeded()) {
            System.out.println("Put capacity not exceeded test failed!");
            counter++;
        }
        if (!testPut_SameKey()) {
            System.out.println("Put same key test failed!");
            counter++;
        }
        if (!testGet_CapacityExceeded()) {
            System.out.println("Get capacity exceeded test failed!");
            counter++;
        }
        if (!testRemove()) {
            System.out.println("Remove test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

