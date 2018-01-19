import java.util.HashSet;
import java.util.Set;

// Task description: Is there a way to create objects in java that are immortal,
// i.e. they manage to avoid being garbage collected? When should such a feature
// be used?
//
// Solution: Every java object is eligible for garbage collection when there are
// no longer any references pointing to it. When an object is picked up by the
// garbage collector for removal, its finalize() method will be called before it
// is deleted from the heap. This method can recreate a reference to the object
// and thus stop it from being deleted. In such cases the JVM will detect that
// the object is again referenced and will refrain from destroying it.
//
// The Immortal class below is resurrecting all its instances. When the finalize
// method runs, it adds a reference of the object into a static Set and thus
// stops it from being destroyed.
//
// Overriding the finalize() method should almost always be avoided and creating
// immortal objects like this should never be done. Resurrecting an object is
// basically the same as intentionally creating a memory leak. Additionally,
// the finalize() method is called by the garbage collector only once. Therefore
// if an object is resurrected and then it is again dereferenced, its finalize()
// method will not be called again and it will be destroyed. Moreover, there
// is also no guarantee that the finalize() method will invoked at all. For
// example if the program terminates for any reason, the JVM simply exists
// without calling any finalizers. Finally, note that as of Java 9 finalize()
// is deprecated.

public class ImmortalObjects {

    public static class Immortal {

        private static final Set<Immortal> IMMORTALS = new HashSet<>();

        public static int size() {
            return IMMORTALS.size();
        }

        @Override
        protected void finalize() throws Throwable {
            IMMORTALS.add(this);
            System.out.println("JVM tried to kill me, but I resurrected myself!");
        }
    }

    private static boolean testImmortal() {
        new Immortal();
        System.gc();

        try {
            Thread.sleep(100);
        } catch (InterruptedException e) { }

        return 1 == Immortal.size();
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testImmortal()) {
            System.out.println("Immortal test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

