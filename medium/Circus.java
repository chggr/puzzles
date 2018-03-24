import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: A circus is designing a tower routine that consists of
// people standing on top of each other's shoulders. Each person in the tower
// must be both shorter and lighter than the person below. Given the heights
// and weights of each person, write a method to compute the largest number of
// people in that tower.
//
// Solution: The implementation below uses recursion with memoization. For every
// person it calculates and memorizes the height of the tower that can be
// created with that person as the base. Once this is done for all people, the
// maximum height overall can be calculated and returned. The runtime complexity
// of this approach is O(n^2) because for each person we have to find the number
// of people that can be placed on top. Space complexity is O(n) due to the
// recursive stack.
//
// Another approach would be to first sort all people based on one parameter,
// e.g. weight, and thus reduce the problem to just one dimension: finding the
// longest increasing subsequence by height. This can be done iteratively by
// using a list of stacks. We iterate through the weight-sorted list of people
// and for every person we find the longest suitable stack that they can be
// appended to. Thus for every person we store a stack with the longest tower
// that ends with that person on top. Then it is a matter of iterating through
// all stacks to find the tallest one. The runtime complexity of this approach
// is again O(n^2) and space complexity also O(n).

public class Circus {

    private static final class Person {
        private final int weight;
        private final int height;

        public Person(int weight, int height) {
            this.weight = weight;
            this.height = height;
        }

        public int getWeight() {
            return weight;
        }

        public int getHeight() {
            return height;
        }
    }

    // Returns all people that can stand above the given person.
    private static List<Person> findAbove(List<Person> people, Person person) {
        List<Person> result = new ArrayList<>();
        for (Person other : people) {
            if (other.equals(person)) continue;
            if (other.weight < person.weight &&
                other.height < person.height) result.add(other);
        }
        return result;
    }

    // Returns the maximum height of a tower with the given person as base.
    private static int find(List<Person> people,
                            Person person,
                            Map<Person, Integer> map) {

        if (map.containsKey(person)) return map.get(person);

        List<Person> above = findAbove(people, person);
        int maxLength = 1;
        for (Person p : above) {
            int length = find(people, p, map);
            if (maxLength < length + 1) maxLength = length + 1;
        }
        map.put(person, maxLength);
        return maxLength;
    }

    private static int find(List<Person> people) {
        Map<Person, Integer> map = new HashMap<>();
        int maxLength = 0;
        for (Person p : people) {
            int length = find(people, p, map);
            if (length > maxLength) maxLength = length;
        }
        return maxLength;
    }

    private static boolean testFindAbove() {
        List<Person> people = Arrays.asList(
                new Person(60, 175),
                new Person(69, 177),
                new Person(63, 176));

        return 0 == findAbove(people, people.get(0)).size() &&
               2 == findAbove(people, people.get(1)).size() &&
               1 == findAbove(people, people.get(2)).size();
    }

    private static boolean testFind() {
        final List<Person> people = Arrays.asList(
                new Person(60, 175),
                new Person(69, 177),
                new Person(63, 176),
                new Person(64, 177),
                new Person(70, 156),
                new Person(56, 180));

        return 3 == find(people);
    }

    private static boolean testFind_SameWeightHeight() {
        final List<Person> people = Arrays.asList(
                new Person(60, 175),
                new Person(60, 175),
                new Person(60, 175),
                new Person(60, 175));

        return 1 == find(people);
    }

    private static boolean testFind_NoPeople() {
        return 0 == find(new ArrayList<>());
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testFindAbove()) {
            System.out.println("Find above test failed!");
            counter++;
        }
        if (!testFind()) {
            System.out.println("Find test failed!");
            counter++;
        }
        if (!testFind_SameWeightHeight()) {
            System.out.println("Find same weight and height test failed!");
            counter++;
        }
        if (!testFind_NoPeople()) {
            System.out.println("Find no people test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

