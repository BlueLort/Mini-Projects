package model;

import javafx.util.Pair;

import java.util.ArrayList;

public class Graph {
    private ArrayList<ArrayList<Pair<Integer, Integer>>> graph;//Adjacency list representation
    private int currentNumberOfNodes = 0;
    //pair array list of parents have key which is vertex and value which is parent

    public Graph(int nNodes) {
        graph = new ArrayList<>(nNodes);
        currentNumberOfNodes = nNodes;
        generateNewNodes();
    }

    public int getCurrentNumberOfNodes() {
        return currentNumberOfNodes;
    }

    public Graph() {
        graph = new ArrayList<>();
    }

    private void generateNewNodes() {
        int diff = currentNumberOfNodes - graph.size();
        for (int i = 0; i < diff; i++) graph.add(new ArrayList<>());
    }

    public void addNodeConnection(int node, Pair<Integer, Integer> toNodeAndCost) {
        if (node > currentNumberOfNodes - 1) {
            currentNumberOfNodes = node + 1;
            generateNewNodes();
        } else if (toNodeAndCost.getKey() > currentNumberOfNodes - 1) {
            currentNumberOfNodes = toNodeAndCost.getKey() + 1;
            generateNewNodes();
        }
        graph.get(node).add(toNodeAndCost);
    }

    public void addNodeConnectionUndirected(int node, int otherNode, int cost) {
        if (node > currentNumberOfNodes - 1) {
            currentNumberOfNodes = node + 1;
            generateNewNodes();
        } else if (otherNode > currentNumberOfNodes - 1) {
            currentNumberOfNodes = otherNode + 1;
            generateNewNodes();
        }
        this.addNodeConnection(node, new Pair<>(otherNode, cost));
        this.addNodeConnection(otherNode, new Pair<>(node, cost));

    }

    public String processDijkstra(int startNode, int endNode) {
        int size = graph.size();
        ArrayList<Boolean> Visited = new ArrayList<>(size);
        ArrayList<Pair<Integer, Integer>> Distances = new ArrayList<>(size);
        ArrayList<Integer> Parents = new ArrayList<>(size);
        for (int i = 0; i < size; i++) {
            Visited.add(false);
            if (i == startNode) Distances.add(new Pair<>(i, 0));
            else Distances.add(new Pair<>(i, Integer.MAX_VALUE));//setting all nodes except start to inf
            Parents.add(-1);
        }
       return processDijkstraShortestPath(startNode, endNode, Distances, Visited, Parents);

    }

    private String processDijkstraShortestPath(int startNode, int endNode, ArrayList<Pair<Integer, Integer>> Distances, ArrayList<Boolean> Visited, ArrayList<Integer> Parents) {

        boolean shortestPathFound = false;

        while (Distances.size() > 0 && !shortestPathFound) {
            Distances.sort((o1, o2) -> o1.getValue() - o2.getValue());
            doDijkstra(Distances.get(0).getKey(), Distances.get(0).getValue(), Distances, Visited, Parents);

            if (Distances.get(0).getKey() == endNode && Distances.get(0).getValue() < Integer.MAX_VALUE)
                shortestPathFound = true;
            Distances.remove(0);
        }
        if (!shortestPathFound) return "NO_PATH";
        String route = Integer.toString(endNode) + " ";
        int k = endNode;
        while (k != startNode) {
            route = route.concat(Integer.toString(Parents.get(k)) + " ");
            k = Parents.get(k);
        }
        return Utility.reverseShortestPathString(route);

    }

    private void doDijkstra(int node, int currentCost, ArrayList<Pair<Integer, Integer>> Distances, ArrayList<Boolean> Visited, ArrayList<Integer> Parents) {
        if (Visited.get(node)) return;
        int size = graph.get(node).size();
        for (int i = 0; i < size; i++) {
            if (replaceDistance(graph.get(node).get(i).getKey(), graph.get(node).get(i).getValue() + currentCost, Distances)) {
                Parents.set(graph.get(node).get(i).getKey(), node);
            }

        }

        Visited.set(node, true);
    }

    private boolean replaceDistance(int node, int newDistance, ArrayList<Pair<Integer, Integer>> Distances) {
        int size = Distances.size();
        for (int i = 0; i < size; i++) {
            if (node == Distances.get(i).getKey()) {
                if (newDistance < Distances.get(i).getValue()) {
                    Distances.set(i, new Pair<>(node, newDistance));
                    return true;
                } else {
                    return false;
                }
            }
        }
        return false;
    }



    public void setCurrentNumberOfNodes(int currentNumberOfNodes) {
        this.currentNumberOfNodes = currentNumberOfNodes;
        generateNewNodes();
    }



    public int getDistance(String[] path) {
        int cost = 0;
        for (int i = 0; i < path.length - 1; i++) {
            int currentNode = Integer.parseInt(path[i]);
            for (int j = 0; j < graph.get(currentNode).size(); j++) {
                if (graph.get(currentNode).get(j).getKey() == Integer.parseInt(path[i + 1])) {
                    cost += graph.get(currentNode).get(j).getValue();
                    break;
                }
            }
        }
        return cost;

    }



}
