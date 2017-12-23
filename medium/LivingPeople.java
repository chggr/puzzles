// Task description: Given a list of people with their birth and death years,
// write a method to return the year with the most number of people alive. You
// may assume that all people were born and died between 1900 and 2000. The
// years each person was born or died in are counted as them being alive. What
// is the most efficient algorithm?
//
// Solution: There are multiple ways to solve this task, below we have written
// three implementations. All solutions use the Person class, which records the
// years a person was born and died in. Other details can be added to that class
// as required (e.g. name, address, etc) but are not necessary for this task.
//
// The simplest solution is to use brute force: go through all years and for
// each one calculate how many people were alive. Identify and return the year
// where most people were alive in. The runtime complexity of this simple
// implementation is O(P * R) where P is the number of people and R the number
// of years under consideration.
//
// The second approach is similar to the first and uses an array to hold the
// number of people alive each year. The algorithm goes through every person and
// increments all array positions between and including their birth and death
// years. It finally goes through the array and identifies the year with the
// most people alive. The runtime complexity of this is O(Y * P + R) where Y
// is the average number of years each person is alive, P is the total number
// of people and R is the year range. In the worst case Y is equal to R and
// the complexity is the same as pure brute force.
//
// The third and final approach uses an array to hold the delta for each year,
// i.e. the amount the population has increased or decreased. We initially go
// all persons and increment the delta on the year they were born and decrement
// the delta in the next year after they died. We finally go through the deltas
// array and keep a count of how many people were alive, to be able to identify
// and return the year where most people were alive. The runtime complexity of
// this approach is O(P + R), where P is the number of persons and R the year
// range.

public class LivingPeople {

    private static final class Person {

        private final int birth;
        private final int death;

        public Person(int birth, int death) {
            this.birth = birth;
            this.death = death;
        }

        int getBirth() {
            return birth;
        }

        int getDeath() {
            return death;
        }
    }

    private static int maxAliveYearBrute(Person[] persons, int min, int max) {
        int maxAlive = 0;
        int maxAliveYear = 0;

        for (int year = min; year <= max; year++) {
            int counter = 0;
            for (Person p : persons) {
                if (p.getBirth() <= year && year <= p.getDeath()) {
                    counter++;
                }
            }
            if (counter > maxAlive) {
                maxAlive = counter;
                maxAliveYear = year;
            }
        }
        return maxAliveYear;
    }

    private static int maxAliveYear(Person[] persons, int min, int max) {
        int[] alive = new int[max - min + 1];
        for (Person p : persons) {
            for (int year = p.getBirth(); year <= p.getDeath(); year++) {
                alive[year - min]++;
            }
        }

        int maxAlive = 0;
        int maxAliveYear = 0;
        for (int i = 0; i < alive.length; i++) {
            if (alive[i] > maxAlive) {
                maxAlive = alive[i];
                maxAliveYear = i + min;
            }
        }
        return maxAliveYear;
    }

    private static int maxAliveYearBetter(Person[] persons, int min, int max) {
        int[] deltas = new int[max - min + 1];

        for (Person p : persons) {
            deltas[p.getBirth() - min]++;
            deltas[p.getDeath() - min + 1]--;
        }

        int maxAlive = 0;
        int maxAliveYear = 0;
        int currentAlive = 0;
        for (int i = 0; i < deltas.length; i++) {
            currentAlive += deltas[i];
            if (currentAlive > maxAlive) {
                maxAlive = currentAlive;
                maxAliveYear = min + i;
            }
        }
        return maxAliveYear;
    }

    private static boolean testComputeYear_NoPersons() {
        return 0 == maxAliveYear(new Person[0], 1900, 2000) &&
               0 == maxAliveYearBrute(new Person[0], 1900, 2000) &&
               0 == maxAliveYearBetter(new Person[0], 1900, 2000);
    }

    private static boolean testComputeYear() {
        Person[] persons = {
                new Person(1950, 1960),
                new Person(1959, 1987),
                new Person(1910, 1955),
                new Person(1956, 1980)
        };

        return 1959 == maxAliveYear(persons, 1900, 2000) &&
               1959 == maxAliveYearBrute(persons, 1900, 2000) &&
               1959 == maxAliveYearBetter(persons, 1900, 2000);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testComputeYear_NoPersons()) {
            System.out.println("Compute year no persons test failed!");
            counter++;
        }
        if (!testComputeYear()) {
            System.out.println("Compute year test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

