import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

// Task description: Write a method to return all valid combinations of n pairs
// of parentheses.
//
// E.g. For n = 3 the output should be: ()()(), (()()), (())(), ()(()), ((()))
//
// Solution: The first implementation below uses a simple approach to generate
// all possible valid combinations of parentheses. Unfortunately this approach
// also creates duplicate results and therefore it is important to use Sets to
// ensure that any duplicates are automatically discarded.
//
// The second approach is also a recursive approach like the first one, but
// does not generate duplicate results and thus is more efficient. It builds
// the string from scratch, adding a left parenthesis and a right parenthesis
// at each step, making sure to eliminate any invalid results by counting how
// many left and right parentheses are remaining.

public class Parentheses {

    private static Set<String> generate(int count, Set<String> input) {
        if (count == 0) return input;

        Set<String> output = new HashSet<>();
        if (input.isEmpty()) {
            output.add("()");
        } else {
            for (String s : input) {
                output.addAll(addParentheses(s));
            }
        }
        return generate(count - 1, output);
    }

    private static Set<String> addParentheses(String input) {
        Set<String> output = new HashSet<>();
        for (int i = 0; i < input.length(); i++) {
            output.add(input.substring(0, i) + "()" + input.substring(i));
        }
        return output;
    }

    private static List<String> generate(int count) {
        if (count == 0) {
            return new ArrayList<>();
        }

        char[] str = new char[2 * count];
        List<String> output = new ArrayList<>();
        addParentheses(output, count, count, str, 0);
        return output;
    }

    private static void addParentheses(List<String> list, int left, int right,
                                       char[] str, int index) {
        if (left < 0 || right < left) {
            return;
        }

        if (right == 0 && left == 0) {
            list.add(String.valueOf(str));
            return;
        }

        str[index] = '(';
        addParentheses(list, left - 1, right, str, index + 1);

        str[index] = ')';
        addParentheses(list, left, right - 1, str, index + 1);
    }

    private static boolean testNoParentheses_Set() {
        Set<String> result = generate(0, new HashSet<>());
        return result.isEmpty();
    }

    private static boolean testNoParentheses_List() {
        List<String> result = generate(0);
        return result.isEmpty();
    }

    private static boolean testSingleParentheses_Set() {
        Set<String> result = generate(1, new HashSet<>());
        return result.size() == 1 && result.contains("()");
    }

    private static boolean testSingleParentheses_List() {
        List<String> result = generate(1);
        return result.size() == 1 && result.contains("()");
    }

    private static boolean testMultipleParentheses_Set() {
        Set<String> result = generate(3, new HashSet<>());
        return result.size() == 5 && result.contains("()()()") &&
               result.contains("(())()") && result.contains("((()))") &&
               result.contains("()(())") && result.contains("(()())");
    }

    private static boolean testMultipleParentheses_List() {
        List<String> result = generate(3);
        return result.size() == 5 && result.contains("()()()") &&
               result.contains("(())()") && result.contains("((()))") &&
               result.contains("()(())") && result.contains("(()())");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testNoParentheses_Set()) {
            System.out.println("No parentheses set test failed!");
            counter++;
        }
        if (!testNoParentheses_List()) {
            System.out.println("No parentheses list test failed!");
            counter++;
        }
        if (!testSingleParentheses_Set()) {
            System.out.println("Single parentheses set test failed!");
            counter++;
        }
        if (!testSingleParentheses_List()) {
            System.out.println("Single parentheses list test failed!");
            counter++;
        }
        if (!testMultipleParentheses_Set()) {
            System.out.println("Multiple parentheses set test failed!");
            counter++;
        }
        if (!testMultipleParentheses_List()) {
            System.out.println("Multiple parentheses list test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

