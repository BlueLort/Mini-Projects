package model;

import java.util.ArrayList;

public class Utility {
    public static String reverseShortestPathString(String input) {
        String[] values = input.split(" ");
        String out = "";
        for (int i = values.length - 1; i >= 0; i--) {
            if (i != 0)
                out += values[i] + " ";
            else
                out += values[i];
        }
        return out;
    }

    public static ArrayList<ArrayList<Boolean>> getVisitedArray(int xSize, int ySize) {
        ArrayList<ArrayList<Boolean>> Visited = new ArrayList<>();
        for (int i = 0; i < ySize; i++) {
            Visited.add(new ArrayList<>());
            for (int j = 0; j < xSize; j++) {
                Visited.get(i).add(false);
            }
        }
        return Visited;
    }
}
