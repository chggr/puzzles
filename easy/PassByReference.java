
// Task description: Please analyse the program below and evaluate what will be
// printed to the standard output. Justify your response.
//
// Solution: This puzzle tests whether a candidate knows how variables are
// passed to methods in Java (i.e. by reference versus by value). Primitive
// variables are passed by value, whereas Objects are passed by reference.
//
// In the first case below, the primitive int variable is passed by value and
// therefore assignment in method assign() will not affect the original. In the
// second case, the Integer variable is passed by reference and this reference
// is repointed to a new auto-boxed Integer object inside method assign(). The
// original reference remains intact. The program will print four zeros, each
// in a new line.
public class PassByReference {

    private static void assign(int variable, int value) {
        variable = value;
    }

    private static void assign(Integer variable, int value) {
        variable = value;
    }

    public static void main(String[] args) {
        int myInt = 0;
        System.out.println(myInt);
        assign(myInt, 1);
        System.out.println(myInt);

        Integer myInteger = 0;
        System.out.println(myInteger);
        assign(myInteger, 1);
        System.out.println(myInteger);
    }
}
