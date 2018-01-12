import java.util.Stack;

// Task description: Given an arithmetic equation string that contains numbers
// and symbols +, -, * and / (no parentheses), write an algorithm to calculate
// the result of the equation.
//
// e.g. For equation "1+2+3+4" the result is 10.0
//                   "1*2+3/4" the result is 2.75
//
// Solution: The operators +, -, * and / do not have the same priority and thus
// we cannot simply evaluate the expression from left to right. Division and
// multiplication have higher priority than addition or subtraction.
//
// The first implementation below is breaking the input string in sub-expressions
// and calls itself recursively to evaluate them until the final result has been
// calculated. The initial expression is first broken down at '+', then the sub
// expressions are broken down at '-', then at '*' and finally at '/'. This
// approach ensures the sub expressions are calculated correctly before arriving
// at a result for the full expression.
//
// The second implementation uses two stacks to keep track of the numbers and
// the operators (numStack and opStack). The input expression is read one
// character at a time, storing all numbers in the numStack and all operators in
// the opStack. After reading each operator, its priority is compared to the
// operator at the top of the opStack. If it is less or equal, then the two
// stacks can be collapsed. This is done by applying the operator at the top of
// the opStack onto the first two numbers in the numStack and storing the result
// back in the numStack. The final result is obtained by collapsing the stacks
// until the opStack is empty and the numStack contains only one element, the
// result.

public class Calculator {

    public static double calculate(String expression) {
        if (expression == null || expression.isEmpty()) {
            return 0.0;
        }

        String[] sub = expression.split("\\+");
        if (sub.length > 1) {
            double result = calculate(sub[0]);
            for (int i = 1; i < sub.length; i++) {
                result += calculate(sub[i]);
            }
            return result;
        }

        sub = expression.split("-");
        if (sub.length > 1) {
            double result = calculate(sub[0]);
            for (int i = 1; i < sub.length; i++) {
                result -= calculate(sub[i]);
            }
            return result;
        }

        sub = expression.split("\\*");
        if (sub.length > 1) {
            double result = calculate(sub[0]);
            for (int i = 1; i < sub.length; i++) {
                result *= calculate(sub[i]);
            }
            return result;
        }

        sub = expression.split("/");
        if (sub.length > 1) {
            double result = calculate(sub[0]);
            for (int i = 1; i < sub.length; i++) {
                result /= calculate(sub[i]);
            }
            return result;
        }

        return Double.parseDouble(expression);
    }

    public static double calculateStacks(String expression) {
        if (expression == null || expression.isEmpty()) {
            return 0.0;
        }

        Stack<Double> numStack = new Stack<>();
        Stack<Character> opStack = new Stack<>();

        String num = "";
        for (Character c : expression.toCharArray()) {
            if (Character.isDigit(c)) {
                num += c;
                continue;
            }
            numStack.push(num.isEmpty() ? 0.0 : Double.parseDouble(num));

            // If the priority of the current operator is less or equal to
            // the priority of the operator at the top of the stack, the
            // stacks can be collapsed.
            while (!opStack.empty() &&
                   priority(c) <= priority(opStack.peek())) {
                collapse(numStack, opStack);
            }

            opStack.push(c);
            num = "";
        }
        numStack.push(Double.parseDouble(num));

        while (!opStack.empty()) {
            collapse(numStack, opStack);
        }
        return numStack.pop();
    }

    // Returns an integer indicating the priority of each operator.
    private static int priority(Character op) {
        return op == '+' ? 1 :
               op == '-' ? 1 :
               op == '*' ? 2 :
               op == '/' ? 2 : 0;
    }

    // Applies the operator at the top of the opStack onto two numbers at the
    // top of the numStack and pushes the result back into the numStack.
    private static void collapse(Stack<Double> numStack,
                                 Stack<Character> opStack) {

        Character op = opStack.pop();
        double numB = numStack.empty() ? 0.0 : numStack.pop();
        double numA = numStack.empty() ? 0.0 : numStack.pop();
        numStack.push(op == '+' ? numA + numB :
                      op == '-' ? numA - numB :
                      op == '*' ? numA * numB :
                      numA / numB);
    }

    private static boolean testCalculate_NullExpression() {
        return 0.0 == calculate(null) &&
               0.0 == calculateStacks(null);
    }

    private static boolean testCalculate_EmptyExpression() {
        return 0.0 == calculate("") &&
               0.0 == calculateStacks("");
    }

    private static boolean testCalculate_SingleNumbers() {
        return 10.0 == calculate("+10") &&
               10.0 == calculateStacks("+10") &&
               -10.0 == calculate("-10") &&
               -10.0 == calculateStacks("-10") &&
               0.0 == calculate("-0") &&
               0.0 == calculateStacks("-0");
    }

    private static boolean testCalculate_AdditionSubtraction() {
        return 10.0 == calculate("1+2+3+4+0") &&
               10.0 == calculateStacks("1+2+3+4+0") &&
               0.0 == calculate("-1+1-1+1-1+1") &&
               0.0 == calculateStacks("-1+1-1+1-1+1") &&
               -7.0 == calculate("2-6-7+4") &&
               -7.0 == calculateStacks("2-6-7+4");
    }

    private static boolean testCalculate_MultiplicationDivision() {
        return 1.0 == calculate("10/5/2") &&
               1.0 == calculateStacks("10/5/2") &&
               100.0 == calculate("10*5*2") &&
               100.0 == calculateStacks("10*5*2") &&
               4.0 == calculateStacks("10/5*2") &&
               4.0 == calculate("10/5*2");
    }

    private static boolean testCalculate() {
        return 10.0 == calculate("10*1+0") &&
               10.0 == calculateStacks("10*1+0") &&
               23.5 == calculate("2*3+5/6*3+15") &&
               23.5 == calculateStacks("2*3+5/6*3+15") &&
               -27.0 == calculate("2-6-7*8/2+5") &&
               -27.0 == calculateStacks("2-6-7*8/2+5") &&
               14.0 == calculate("2*6-10+3*4") &&
               14.0 == calculateStacks("2*6-10+3*4");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testCalculate_NullExpression()) {
            System.out.println("Null expression calculate test failed.");
            counter++;
        }
        if (!testCalculate_EmptyExpression()) {
            System.out.println("Empty expression calculate test failed.");
            counter++;
        }
        if (!testCalculate_SingleNumbers()) {
            System.out.println("Single numbers calculate test failed.");
            counter++;
        }
        if (!testCalculate_AdditionSubtraction()) {
            System.out.println("Addition / subtraction calculate test failed.");
            counter++;
        }
        if (!testCalculate_MultiplicationDivision()) {
            System.out.println("Multiplication / division calculate test failed.");
            counter++;
        }
        if (!testCalculate()) {
            System.out.println("Calculate test failed.");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

