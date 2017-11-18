// Task description: Read the program below, what will it print on screen?
//
// Solution: The program is using try / catch / finally but the code inside
// the try block throws an error. The finally block will be executed just after
// the try block exits, but before execution is resumed in the calling method.
//
// The only cases where a finally block will not get executed are:
// 1) The JVM exits during try / catch block execution.
// 2) The thread is killed during try / catch block execution.
//
// The following lines will be printed on screen:
//
// start
// methodB try start
// catch
// methodA
// finally
// methodA return | methodB catch
// end

public class Finally {

    public static String methodA() {
        System.out.println("methodA");
        return "methodA return";
    }

    public static String methodB() {
        int a = 0;
        int b = 1;

        try {
            System.out.println("methodB try start");
            b /= a;
            System.out.println("methodB try end");
            return "methodB return";
        } catch (Exception e) {
            System.out.println("catch");
            return methodA() + " | methodB catch";
        } finally {
            System.out.println("finally");
        }
    }

    public static void main(String[] args) {
        System.out.println("start");
        System.out.println(methodB());
        System.out.println("end");
    }
}

