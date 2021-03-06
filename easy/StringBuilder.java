// Task description: Implement your own simplified version of StringBuilder, a
// class that is backed by a dynamically resizing array and allows for fast
// concatenation of Strings.
//
// Solution: In this implementation we have chosen to double the underlying
// array size once space is exhausted.

public class StringBuilder {

    private char[] array = new char[8];
    private int cursor = 0;

    public String toString() {
        return String.valueOf(array, 0, cursor);
    }

    public StringBuilder append(final String input) {
        resize(input.length());
        for (int i = 0; i < input.length(); i++) {
            array[cursor] = input.charAt(i);
            cursor++;
        }
        return this;
    }

    public StringBuilder append(final char input) {
        this.append(Character.toString(input));
        return this;
    }

    public StringBuilder append(final int input) {
        this.append(Integer.toString(input));
        return this;
    }

    public StringBuilder append(final long input) {
        this.append(Long.toString(input));
        return this;
    }

    public StringBuilder append(final double input) {
        this.append(Double.toString(input));
        return this;
    }

    private void resize(final int addCapacity) {
        if ((cursor + addCapacity) <= array.length) {
            return;
        }

        int newCapacity = array.length * 2;
        while (newCapacity < cursor + addCapacity) {
            newCapacity *= 2;
        }

        char[] newArray = new char[newCapacity];
        for (int i = 0; i < cursor; i++) {
            newArray[i] = array[i];
        }
        array = newArray;
    }

    private static boolean testToString_EmptyBuilder() {
        final StringBuilder builder = new StringBuilder();
        return "".equals(builder.toString());
    }

    private static boolean testToString() {
        final StringBuilder builder = new StringBuilder();
        builder.append("Hello ");
        builder.append("world!");
        return "Hello world!".equals(builder.toString());
    }

    private static boolean testAppend_VariousTypes() {
        final StringBuilder builder = new StringBuilder();
        builder.append("Hello ");
        builder.append(1);
        builder.append(' ');
        builder.append(3.141517);
        builder.append('-');
        builder.append(2L);
        return "Hello 1 3.141517-2".equals(builder.toString());
    }

    private static boolean testAppend_EmptyInput() {
        final StringBuilder builder = new StringBuilder();
        builder.append("");
        builder.append("Hello");
        builder.append("");
        return "Hello".equals(builder.toString());
    }

    private static boolean testAppend_LongInput() {
        final StringBuilder builder = new StringBuilder();
        builder.append("Lorem ipsum dolor sit amet");
        return "Lorem ipsum dolor sit amet".equals(builder.toString());
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testToString_EmptyBuilder()) {
            System.out.println("ToString test with empty builder failed!");
            counter++;
        }
        if (!testToString()) {
            System.out.println("ToString test failed!");
            counter++;
        }
        if (!testAppend_VariousTypes()) {
            System.out.println("Append test with various types failed!");
            counter++;
        }
        if (!testAppend_EmptyInput()) {
            System.out.println("Append test with empty input failed!");
            counter++;
        }
        if (!testAppend_LongInput()) {
            System.out.println("Append test with long input failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

