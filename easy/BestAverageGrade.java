import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// Task description: Given an array of String arrays that contain the name of a
// student and their grade, write a method to return the best average grade in
// the data set.
//
// E.g. for the following data, the method should return 88.0
//      {{"George", "25"},
//       {"Nick", "73"},
//       {"Nick", "45"},
//       {"George", "95"},
//       {"Stuart", "88"},
//       {"Nick", "30"}};
//
// Solution: The implementation below transforms the original data set into a
// Map<String, List<Double>> where we store all grades for each student. It then
// goes through all values in the map, calculating the average grade for every
// student and returning the maximum. If N is the total number of records, both
// space and runtime complexities of this algorithm are O(N).

public class BestAverageGrade {

    private static double average(List<Double> values) {
        double sum = 0;
        for (Double value : values) {
            sum += value;
        }
        return sum / values.size();
    }

    private static double bestAverage(String[][] records) {
        if (records == null) return 0.0;

        Map<String, List<Double>> data = new HashMap<>();
        for (String[] record : records) {
            String name = record[0];
            Double grade = Double.valueOf(record[1]);

            List<Double> grades = data.get(name);
            if (grades == null) data.put(name, new ArrayList<>());
            data.get(name).add(grade > 0.0 ? grade : 0.0);
        }

        double max = 0.0;
        double current = 0.0;
        for (List<Double> grades : data.values()) {
            current = average(grades);
            if (current > max) max = current;
        }
        return max;
    }

    private static boolean testBestAverage_Null() {
        return 0.0 == bestAverage(null);
    }

    private static boolean testBestAverage_Empty() {
        return 0.0 == bestAverage(new String[0][0]);
    }

    private static boolean testBestAverage() {
        String[][] records = {{"George", "25"},
                              {"Nick", "73"},
                              {"Nick", "45"},
                              {"George", "95"},
                              {"Stuart", "88"},
                              {"Nick", "30"}};

        return 88.0 == bestAverage(records);
    }

    private static boolean testBestAverage_Negative() {
        String[][] records = {{"George", "25"},
                              {"Nick", "-73"},
                              {"Nick", "45"},
                              {"George", "-95"},
                              {"Stuart", "-88"},
                              {"Nick", "30"}};

        return 25.0 == bestAverage(records);
    }

    public static void main(String[] args) {
        int counter = 0;
        if (!testBestAverage_Null()) {
            System.out.println("Best average null test failed!");
            counter++;
        }
        if (!testBestAverage_Empty()) {
            System.out.println("Best average empty test failed!");
            counter++;
        }
        if (!testBestAverage()) {
            System.out.println("Best average test failed!");
            counter++;
        }
        if (!testBestAverage_Negative()) {
            System.out.println("Best average negative test failed!");
            counter++;
        }
        System.out.println(counter + " tests failed.");
    }
}

