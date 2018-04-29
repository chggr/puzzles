import java.util.Arrays;

// Task description: Write a method to solve cryptarithmetic puzzles often found
// in newspapers and magazines. The goal is to assign a digit from 0 to 9 to
// each letter so that the arithmetic works out correctly. All occurrences of a
// letter must be assigned the same digit and no digit can be assigned to more
// than one letter.
//
// E.g. puzzle:         SEND + MORE = MONEY
//      solution:       D = 1, E = 5, M = 0, N = 3, O = 8, R = 2, S = 7, Y = 6
//      verification:   7531 + 0825 = 08356
//
// Solution: A brute force approach would be to first get a list of distinct
// letters, attempt to assign a number to each letter and finally check if the
// assignment solves the puzzle. The number of possible assignments that need
// to be checked is 10 choose k = 10! / (k! * (n - k)!), where k is the number
// of distinct letters. Therefore the runtime complexity is O(k!) which can be
// very slow for large k.
//
// The implementation below uses a smarter recursive algorithm with backtracking
// to arrive to a solution faster. It takes advantage of the structure of the
// puzzle to quickly eliminate recursive paths that do not lead to a solution.
// It starts from the last index of the given words and attempts to assign
// values to letters while also checking whether each assignment is valid. This
// helps identify invalid assignments early and avoid going down dead-end paths.
// Although the code is more complex than the simple brute force approach, the
// additional logic leads to significant improvements in efficiency and thus
// making it more feasible to solve large puzzles.

public class CryptarithmeticPuzzle {

    // Converts the given String to an integer using the provided letter to
    // digit assignments up to the specified index.
    private static int convert(String s, int index, int[] assign) {
        int result = 0;
        for (int i = 0; i < index; i++) {
            if (i >= s.length()) break;
            int digit = assign[s.charAt(s.length() - i - 1) - 'A'];
            result += Math.pow(10, i) * digit;
        }
        return result;
    }

    // Checks that the given assignment is valid up to the given index,
    // based on the provided String and its integer representation.
    private static boolean checkAssignment(String a, int aInt,
                                           int index, int[] assign) {
        for (int i = 0; i < index; i++) {
            int digit = aInt % 10;
            aInt /= 10;

            if (i >= a.length()) break;
            char c = a.charAt(a.length() - i - 1);
            if (assign[c - 'A'] != digit) return false;
        }
        return true;
    }

    // Checks whether the provided digit to character assignments are valid
    // up to the specified index.
    private static boolean isValid(String a, String b, String res,
                                   int index, int[] assign) {
        int aInt = convert(a, index, assign);
        int bInt = convert(b, index, assign);
        int resInt = aInt + bInt;
        return checkAssignment(res, resInt, index, assign);
    }

    private static boolean find(int[] array, int target) {
        for (int i = 0; i < array.length; i++) {
            if (array[i] == target) return true;
        }
        return false;
    }

    private static boolean solve(String a, String b, String res,
                                 int index, int[] assign) {

        // All letters have been assigned, check the assignments are valid.
        if (index >= a.length() &&
            index >= b.length() &&
            index >= res.length()) {
            return isValid(a, b, res, index + 1, assign);
        }

        // Check and assign the character in the first string.
        if (index < a.length()) {
            char aChar = a.charAt(a.length() - index - 1);
            if (assign[aChar - 'A'] == -1) {
                for (int i = 0; i < 10; i++) {
                    if (find(assign, i)) continue;

                    assign[aChar - 'A'] = i;
                    if (solve(a, b, res, index, assign)) return true;
                    assign[aChar - 'A'] = -1;
                }
            }
        }

        // Check and assign the character in the second string.
        if (index < b.length()) {
            char bChar = b.charAt(b.length() - index - 1);
            if (assign[bChar - 'A'] == -1) {
                for (int i = 0; i < 10; i++) {
                    if (find(assign, i)) continue;

                    assign[bChar - 'A'] = i;
                    if (solve(a, b, res, index, assign)) return true;
                    assign[bChar - 'A'] = -1;
                }
            }
        }

        // Check and assign the character in the result.
        if (index < res.length()) {
            char rChar = res.charAt(res.length() - index - 1);
            if (assign[rChar - 'A'] == -1) {
                for (int i = 0; i < 10; i++) {
                    if (find(assign, i)) continue;

                    assign[rChar - 'A'] = i;
                    if (solve(a, b, res, index, assign)) return true;
                    assign[rChar - 'A'] = -1;
                }
            }
        }

        // All letters for this index have been assigned, check for validity
        // and backtrack if the result so far is not valid.
        if (isValid(a, b, res, index, assign)) {
            return solve(a, b, res, index + 1, assign);
        } else {
            return false;
        }
    }

    private static int[] solve(String a, String b, String res) {
        int[] assign = new int[26];
        for (int i = 0; i < 26; i++) {
            assign[i] = -1;
        }

        return solve(a, b, res, 0, assign) ? assign : null;
    }

    private static boolean testConvert() {
        int[] assign = {1, 2, 3, 4, 5};
        return 54321 == convert("HGFEDCBA", 5, assign) &&
               4321 == convert("HGFEDCBA", 4, assign) &&
               321 == convert("HGFEDCBA", 3, assign) &&
               21 == convert("HGFEDCBA", 2, assign) &&
               1 == convert("HGFEDCBA", 1, assign) &&
               0 == convert("HGFEDCBA", 0, assign);
    }

    private static boolean testIsValid() {
        int[] assign = {1, 2, 3, 4, 5};
        return isValid("AB", "AB", "BD", 2, assign) &&
               !isValid("AB", "AB", "AB", 2, assign);
    }

    private static boolean testSolve() {
        int[] result = solve("SEND", "MORE", "MONEY");
        int[] expected = {-1, -1, -1, 1, 5, -1, -1, -1, -1,
                          -1, -1, -1, 0, 3, 8, -1, -1, 2,
                          7, -1, -1, -1, -1, -1, 6, -1};
        return Arrays.equals(result, expected);
    }

    private static boolean testSolveImpossible() {
        return null == solve("ABCDE", "ABCDE", "ABCDE");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testConvert()) {
            counter++;
            System.out.println("Convert test failed!");
        }
        if (!testIsValid()) {
            counter++;
            System.out.println("IsValid test failed!");
        }
        if (!testSolve()) {
            counter++;
            System.out.println("Solve test failed!");
        }
        if (!testSolveImpossible()) {
            counter++;
            System.out.println("Solve impossible test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

