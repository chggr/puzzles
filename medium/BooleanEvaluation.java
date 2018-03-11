import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: Given a boolean expression consisting of symbols 0 (false),
// 1 (true), & (AND), | (OR) and ^ (XOR) and a desired boolean result, implement
// a method to count the number of ways of parenthesizing the expression such
// that it evaluates to the desired result.
//
// e.g. For expression 1^0|0|1 the method should return:
//      (1)^((0)|((0)|(1))) and (1)^(((0)|(0))|(1))
//
// Solution: The implementation below uses recursion with memoization to compute
// the result. It goes through all positions where there are operators and
// recursively calculates the different ways that the left part can be true or
// false and the right part can be true or false. Finally, it combines the
// results according to the operator at that position. A map is used to store
// previous results and avoid computing the same expression multiple times.

public class BooleanEvaluation {

    // Combines two lists of strings using the given operator.
    private static List<String> combine(List<String> left,
                                        List<String> right,
                                        String operator) {

        List<String> results = new ArrayList<>();
        for (String l : left) {
            for (String r : right) {
                results.add("(" + l + ")" + operator + "(" + r + ")");
            }
        }
        return results;
    }

    private static List<String> evaluate(String expr, boolean target,
                                         Map<String, List<String>> memo) {

        String key = expr + "=>" + target;
        if (memo.containsKey(key)) return memo.get(key);
        if (expr == null || expr.isEmpty()) return new ArrayList<>();

        List<String> results = new ArrayList<>();
        if (expr.length() == 1) {
            if ("1".equals(expr) && target) results.add("1");
            if ("0".equals(expr) && !target) results.add("0");
            memo.put(key, results);
            return memo.get(key);
        }

        for (int i = 1; i < expr.length(); i += 2) {
            char op = expr.charAt(i);
            String left = expr.substring(0, i);
            String right = expr.substring(i + 1);

            List<String> leftFalse = evaluate(left, false, memo);
            List<String> leftTrue = evaluate(left, true, memo);
            List<String> rightFalse = evaluate(right, false, memo);
            List<String> rightTrue = evaluate(right, true, memo);

            if ('&' == op) {
                if (target) {
                    results.addAll(combine(leftTrue, rightTrue, "&"));
                } else {
                    results.addAll(combine(leftTrue, rightFalse, "&"));
                    results.addAll(combine(leftFalse, rightTrue, "&"));
                    results.addAll(combine(leftFalse, rightFalse, "&"));
                }
            } else if ('|' == op) {
                if (target) {
                    results.addAll(combine(leftTrue, rightFalse, "|"));
                    results.addAll(combine(leftFalse, rightTrue, "|"));
                    results.addAll(combine(leftTrue, rightTrue, "|"));
                } else {
                    results.addAll(combine(leftFalse, rightFalse, "|"));
                }
            } else if ('^' == op) {
                if (target) {
                    results.addAll(combine(leftTrue, rightFalse, "^"));
                    results.addAll(combine(leftFalse, rightTrue, "^"));
                } else {
                    results.addAll(combine(leftTrue, rightTrue, "^"));
                    results.addAll(combine(leftFalse, rightFalse, "^"));
                }
            }
        }

        memo.put(key, results);
        return results;
    }

    private static boolean testEvaluate_NoResults() {
        List<String> results = evaluate("1&1&1&1", false, new HashMap<>());
        return results.isEmpty();
    }

    private static boolean testEvaluate_TwoResults() {
        List<String> results = evaluate("1^0|0|1", false, new HashMap<>());
        return 2 == results.size() &&
               results.contains("(1)^((0)|((0)|(1)))") &&
               results.contains("(1)^(((0)|(0))|(1))");
    }

    private static boolean testEvaluate_ManyResults() {
        List<String> results = evaluate("0&0&0&1^1|0", true, new HashMap<>());
        return 10 == results.size() &&
               results.contains("(((0)&((0)&((0)&(1))))^(1))|(0)") &&
               results.contains("(((0)&(((0)&(0))&(1)))^(1))|(0)") &&
               results.contains("((((0)&(0))&((0)&(1)))^(1))|(0)") &&
               results.contains("((((0)&((0)&(0)))&(1))^(1))|(0)") &&
               results.contains("(((((0)&(0))&(0))&(1))^(1))|(0)") &&
               results.contains("((0)&((0)&((0)&(1))))^((1)|(0))") &&
               results.contains("((0)&(((0)&(0))&(1)))^((1)|(0))") &&
               results.contains("(((0)&(0))&((0)&(1)))^((1)|(0))") &&
               results.contains("(((0)&((0)&(0)))&(1))^((1)|(0))") &&
               results.contains("((((0)&(0))&(0))&(1))^((1)|(0))");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testEvaluate_NoResults()) {
            counter++;
            System.out.println("No results test failed!");
        }
        if (!testEvaluate_TwoResults()) {
            counter++;
            System.out.println("Two results test failed!");
        }
        if (!testEvaluate_ManyResults()) {
            counter++;
            System.out.println("Many results test failed!");
        }
        System.out.println(counter + " tests failed.");
    }
}

