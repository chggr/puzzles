// Task description: Write a method that will translate an Excel column name
// (A, B, C, D... AA, AB, AC... AAA, AAB, etc) into an integer.
//
// E.g. for input "A" the method should return 1
//      for input "AA" the method should return 27

public class Excel {

    private static int toInt(String cell) {
        int result = 0;
        for (int i = 0; i < cell.length(); i++) {
            result *= 26;
            result += cell.charAt(i) - 'A' + 1;
        }
        return result;
    }

    private static boolean testOneLetter() {
        return 1 == toInt("A") &&
               2 == toInt("B") &&
               26 == toInt("Z");
    }

    private static boolean testTwoLetters() {
        return 27 == toInt("AA") &&
               195 == toInt("GM") &&
               510 == toInt("SP");
    }

    private static boolean testThreeLetters() {
        return 703 == toInt("AAA") &&
               830 == toInt("AEX") &&
               1024 == toInt("AMJ");
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testOneLetter()) {
            System.out.println("One letter test failed!");
            counter++;
        }
        if (!testTwoLetters()) {
            System.out.println("Two letters test failed!");
            counter++;
        }
        if (!testThreeLetters()) {
            System.out.println("Three letters test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

