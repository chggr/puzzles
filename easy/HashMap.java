// Task description: Implement your own simplified version of a HashMap, a data
// structure that is able to store key / value pairs and retrieve a value
// efficiently in O(1) based on a given key.
//
// Solution: In this implementation we use an array of linked lists to hold the
// HashMap entries. Upon get() or put(), the hashcode of the key is calculated
// and subsequently used to determine the position in the table where the entry
// should reside. Implementing Entry as a linked list is necessary because of
// possible collisions.

public class HashMap<K,V> {

    private final class Entry<K,V> {
        private Entry<K,V> next;
        private K key;
        private V value;

        public Entry(final Entry<K,V> next, final K key, final V value) {
            this.next = next;
            this.key = key;
            this.value = value;
        }

        public Entry<K,V> getNext() {
            return next;
        }

        public void setNext(Entry<K,V> next) {
            this.next = next;
        }

        public K getKey() {
            return this.key;
        }

        public void setKey(K key) {
            this.key = key;
        } 

        public V getValue() {
            return value;
        }

        public void setValue(V value) {
            this.value = value;
        }
    }

    private final Entry<K,V>[] array;

    public HashMap(final int size) {
        // Array of generics is not supported, thus casting is required.
        this.array = (Entry<K,V>[]) new Entry[size];
    }

    public void put(K key, V value) {
        int position = Math.abs(key.hashCode()) % array.length;

        if (array[position] == null) {
            array[position] = new Entry<>(null, key, value);
        } else {
            Entry<K,V> entry = array[position];
            while (!entry.getKey().equals(key) && entry.getNext() != null) {
                entry = entry.getNext();
            }

            if (entry.getKey().equals(key)) {
                entry.setValue(value);
            } else {
                entry.setNext(new Entry<>(null, key, value));
            }
        }
    }

    public V get(K key) {
        int position = Math.abs(key.hashCode()) % array.length;

        if (array[position] == null) {
            return null;
        } else {
            Entry<K,V> entry = array[position];
            while (!entry.getKey().equals(key) && entry.getNext() != null) {
                entry = entry.getNext();
            }
            return entry.getKey().equals(key) ? entry.getValue() : null;
        }
    }

    private static boolean testGet_UnknownKey() {
        final HashMap<String,Integer> table = new HashMap<>(1000);
        return table.get("testKey") == null;
    }

    private static boolean testPut_NullValue() {
        final HashMap<String,Integer> table = new HashMap<>(1000);
        table.put("testKey", null);
        return table.get("testKey") == null;
    }

    private static boolean testPut() {
        final HashMap<String,Integer> table = new HashMap<>(1000);
        table.put("testKey", 100);
        return table.get("testKey") == 100;
    }

    private static boolean testPut_Twice() {
        final HashMap<String,Integer> table = new HashMap<>(1000);
        table.put("testKey", 100);
        table.put("testKey", 1000);
        return table.get("testKey") == 1000;
    }

    public static void main(String[] argc) {
        int counter = 0;
        if (!testGet_UnknownKey()) {
            System.out.println("Get unknown key test failed!");
            counter++;
        }
        if (!testPut_NullValue()) {
            System.out.println("Put null value test failed!");
            counter++;
        }
        if (!testPut()) {
            System.out.println("Put test failed!");
            counter++;
        }
        if (!testPut_Twice()) {
            System.out.println("Put twice test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

