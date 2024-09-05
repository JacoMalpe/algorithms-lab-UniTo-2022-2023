package src.Graph;

import src.Edge.AbstractEdge;
import src.Edge.Edge;

import java.util.*;

public class Graph<V,L> implements AbstractGraph<V,L>{

    private HashMap<V, HashMap<V, L>> map;
    private boolean directed;
    private boolean labelled;

    public Graph(boolean directed, boolean labelled){
        this.map = new HashMap<>();
        this.directed = directed;
        this.labelled = labelled;
    }

    /**
     * @return true if the graph is directed, false otherwise
     */
    @Override
    public boolean isDirected() {
        return directed;
    }

    /**
     * @return true if the graph is labelled, false otherwise
     */
    @Override
    public boolean isLabelled() {
        return labelled;
    }

    /**
     * @param a a node do add to the graph
     * @return true if the node was not already in the graph, false otherwise
     */
    @Override
    public boolean addNode(V a) {
        if(containsNode(a))
            return false;
        map.put(a, new HashMap<>());
        return true;
    }

    /**
     * @param a starting node
     * @param b ending node
     * @param l label
     * @return true if the new edge is inserted correctly, false otherwise
     */
    @Override
    public boolean addEdge(V a, V b, L l) {
        if(!containsNode(a) || !containsNode(b) || containsEdge(a, b) || (labelled && l == null) || (!labelled && l != null))
            return false;
        map.get(a).put(b, l);
        if(!isDirected())
            map.get(b).put(a, l);
        return true;
    }

    /**
     * @param a node to search
     * @return true if it is in the graph, no otherwise
     */
    @Override
    public boolean containsNode(V a) {
        return map.containsKey(a);
    }

    /**
     * @param a starting node
     * @param b ending node
     * @return true if the graph contains an edge from a to b, no otherwise
     */
    @Override
    public boolean containsEdge(V a, V b) {
        if(!containsNode(a))
            return false;
        return map.get(a).containsKey(b);
    }

    /**
     * @param a node to remove
     * @return true if the node is removed correctly, false if it was not in the graph
     */
    @Override
    public boolean removeNode(V a) {
        if(!containsNode(a))
            return false;
        if(!directed)
            for(V neighbour: getNeighbours(a))
                map.get(neighbour).remove(a);
        else
            for (HashMap<V, L> edges : map.values())
                edges.remove(a);
        map.remove(a);
        return true;
    }

    /**
     * @param a starting node
     * @param b ending node
     * @return true if the edge between a and b is removed correctly, false if it wasn't in the graph
     */
    @Override
    public boolean removeEdge(V a, V b) {
        if(!containsEdge(a, b))
            return false;
        map.get(a).remove(b);
        if(!directed)
            map.get(b).remove(a);
        return true;
    }

    /**
     * @return the number of nodes in the graph
     */
    @Override
    public int numNodes() {
        return map.size();
    }

    /**
     * @return the number of edges in the graph
     */
    @Override
    public int numEdges() {
        int count = 0;
        for (HashMap<V, L> edges : map.values()) {
            count += edges.size();
        }
        return isDirected() ? count : count / 2;
    }

    /**
     * @return a collection of all the nodes in the graph
     */
    @Override
    public AbstractCollection<V> getNodes() {
        return new HashSet<>(map.keySet());
    }

    /**
     * @return a collection of all the edges in the graph
     */
    @Override
    public Collection<AbstractEdge<V, L>> getEdges() {
        HashSet<AbstractEdge<V, L>> edges = new HashSet<>();
        for (Map.Entry<V, HashMap<V, L>> node : map.entrySet())
            for (Map.Entry<V, L> edge : node.getValue().entrySet())
                edges.add(new Edge<>(node.getKey(), edge.getKey(), edge.getValue()));
        return edges;
    }

    /**
     * @param a 
     * @return a collection of all the adjacent nodes of a
     */
    @Override
    public AbstractCollection<V> getNeighbours(V a) {
        if(!containsNode(a))
            return null;
        return new HashSet<>(map.get(a).keySet());
    }

    /**
     * @param a 
     * @param b
     * @return the label of the edge between a and b, null otherwise
     */
    @Override
    public L getLabel(V a, V b) {
        if(!containsNode(a) || !containsNode(b))
            return null;
        return map.get(a).get(b);
    }
}
