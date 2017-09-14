// Task description: Implement a method to perform basic string compression by
// using the counts of repeated characters. Each character should be followed
// by the number of times it appears, please see examples below for more
// details. If the size of the compressed string is larger or equal to the
// original, the method should return the original.
//
// E.g. For input "abc" it should return "abc".
//      For input "aaabbbccccca" it should return "a3b4c5a1".

public class StringCompression {

    private static String compress(String input) {

        if (input == null) {
            return null;
        }
        if (input.isEmpty()) {
            return input;
        }

        final StringBuilder sb = new StringBuilder();
        int currentCount = 1;
        char currentChar = input.charAt(0);

        for (int i = 1; i < input.length(); i++) {
            if (input.charAt(i) == currentChar) {
                currentCount++;
            } else {
                sb.append(currentChar).append(currentCount);
                currentCount = 1;
                currentChar = input.charAt(i);
            }
        }
        sb.append(currentChar).append(currentCount);
        final String output = sb.toString();
        return output.length() < input.length() ? output : input;
    }

    public static boolean testCompress() {
        return "a3b4c5a1".equals(compress("aaabbbbccccca"));
    }

    public static boolean testCompress_NoCompression() {
        return "abcd".equals(compress("abcd"));
    }

    public static boolean testCompress_NullInput() {
        return null == compress(null);
    }

    public static boolean testCompress_EmptyInput() {
        return "".equals(compress(""));
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testCompress()) {
            System.out.println("Compress test failed!");
            counter++;
        }
        if (!testCompress_NoCompression()) {
            System.out.println("No compression test failed!");
            counter++;
        }
        if (!testCompress_NullInput()) {
            System.out.println("Null input compression test failed!");
            counter++;
        }
        if (!testCompress_EmptyInput()) {
            System.out.println("Empty input compression test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

