// Task description: Implement your own simplified version of ArrayList, a data
// structure that is able to store Objects and is backed by a dynamically
// resizing array.
//
// Solution: In this implementation we have chosen to double the underlying
// array size once space is exhausted and halve the size if only just a quarter
// of it is used.

public class ArrayList<T> {

    private T[] array = (T[]) new Object[8];
    private int cursor = 0;

    private void resize() {
        T[] newArray = null;
        if (cursor == array.length) {
            newArray = (T[]) new Object[array.length * 2];
        } else if (cursor < array.length / 4 && array.length > 8) {
            newArray = (T[]) new Object[array.length / 2];
        }

        if (newArray != null) {
            for (int i = 0; i < cursor; i++) {
                newArray[i] = array[i];
            }
            array = newArray;
        }
    }

    public int size() {
        return cursor;
    }

    public T get(int position) {
        if (position >= cursor) {
            throw new IndexOutOfBoundsException();
        }
        return array[position];
    }

    public void add(T element) {
        resize();
        array[cursor] = element;
        cursor++;
    }

    public void insert(int position, T element) {
        if (position > cursor) {
            throw new IndexOutOfBoundsException();
        }
        resize();
        for (int i = cursor; i < position; i--) {
            array[i] = array[i - 1];
        }
        array[position] = element;
        cursor++;
    }

    public void delete(int position) {
        if (position >= cursor) {
            throw new IndexOutOfBoundsException();
        }
        for (int i = position; i < cursor - 1; i++) {
            array[i] = array[i + 1];
        }
        cursor--;
        resize();
    }

    private static boolean testSize_EmptyList() {
        final ArrayList<String> list = new ArrayList<>();
        return list.size() == 0;
    }

    private static boolean testSize_PopulatedList() {
        final ArrayList<String> list = new ArrayList<>();
        list.add("testString");
        return list.size() == 1;
    }

    private static boolean testAdd_ManyElements() {
        final ArrayList<String> list = new ArrayList<>();
        for (int i = 0; i < 1000; i++) {
            list.add("testString");
        }

        for (int i = 0; i < 1000; i++) {
            if (list.get(i) != "testString") return false;
        }
        return true;
    }

    private static boolean testInsert() {
        final ArrayList<String> list = new ArrayList<>();
        for (int i = 0; i < 1000; i++) {
            list.add("testString");
        }
        list.insert(0, "insertedString");
        return list.get(0).equals("insertedString");
    }

    private static boolean testDelete() {
        final ArrayList<String> list = new ArrayList<>();
        for (int i = 0; i < 1000; i++) {
            list.add("testString");
        }
        list.delete(0);
        return list.size() == 999;
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testSize_EmptyList()) {
            System.out.println("Size of empty list test failed!");
            counter++;
        }
        if (!testSize_PopulatedList()) {
            System.out.println("Size of populated list test failed!");
            counter++;
        }
        if (!testAdd_ManyElements()) {
            System.out.println("Add many elements test failed!");
            counter++;
        }
        if (!testInsert()) {
            System.out.println("Insert test failed!");
            counter++;
        }
        if (!testDelete()) {
            System.out.println("Delete test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

